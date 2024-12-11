"""Acest modul conține clasa ThreadPool și clasa TaskRunner,
care gestionează threadurile. Tot aici, se calculează rezultatele
requesturilor"""
import json
import os
from queue import Queue
from threading import Thread
import threading
from app.data_ingestor import DataIngestor
from app.logging import logger


class ThreadPool:
    def __init__(self):
        logger.info('Intrare în funcția __init__() din ThreadPool')
        self.num_threads = self._get_thread_count()
        self.graceful_shutdown_flag = False
        self.queue = Queue()
        self.pairs = {}
        self.my_lock = threading.Lock()
        self.job_id_counter = 0
        self.finished_jobs = 0
        self.pool = []

        if not os.path.exists('./app/results'):
            os.makedirs('./app/results')

        # Se crează firele de execuție, se adaugă în pool și se pornesc
        for _ in range(self.num_threads):
            thread = TaskRunner(self.queue, self.graceful_shutdown_flag, self.pairs)
            self.pool.append(thread)
        for thread in self.pool:
            thread.start()
        logger.info('Ieșire din funcția __init__() din ThreadPool')

    # Metoda ce returnează numărul de fire de execuție suportate de sistem
    def _get_thread_count(self):
        logger.info('Intrare în get_thread_count()')
        if 'TP_NUM_OF_THREADS' in os.environ:
            logger.info('Iesire din get_thread_count() cu parametrul TP_NUM_OF_THREADS')
            return int(os.environ['TP_NUM_OF_THREADS'])
        else:
            logger.info('Iesire din get_thread_count() cu parametrul {os.cpu_count()}')
            return os.cpu_count()


class TaskRunner(Thread):

    def __init__(self, queue, graceful_shutdown_flag, pairs):
        logger.info('Intrare în funcția __init__() din TaskRunner')
        super().__init__()
        self.queue = queue
        self.pairs = pairs
        self.graceful_shutdown_flag = graceful_shutdown_flag
        self.results_file = "./app/results/"
        self.data_ingestor = DataIngestor("./nutrition_activity_obesity_usa_subset.csv")
        logger.info('Ieșire din funcția __init__() din ThreadPool')

    def run(self):
        # Cat timp nu s-a primit semnal de oprire și coada nu este goală
        while not self.graceful_shutdown_flag:
            if not self.queue.empty():
                # Se extrage un job din coadă și se execută în funcție de tip
                job_data = self.queue.get()

                mytype, job_id, data = job_data
                logger.info('Executare task de tipul {mytype} cu datele {data} și job_id {job_id}')
                result = self.execute_task(mytype, data)

                if result is not None:
                    # Se creează un fișier în care se scrie rezultatul
                    result_path = os.path.join(self.results_file, f"job_id_{job_id}.json")
                    logger.info('Scriere rezultat în fișierul {result_path}')

                    with open(result_path, 'w', encoding='utf-8') as f:
                        f.write(result)

                    # Se actualizează statusul job-ului în dicționars
                    if  "job_id_" + str(job_id) in self.pairs:
                        self.pairs["job_id_" + str(job_id)] = "done"


    def execute_task(self, mytype, data):
        # Pentru tipuri de task-uri asemănătoare, ce necesită prelucrea tuturor statelor
        if (mytype == "best5") or (mytype == "worst5") or (mytype == "states_mean") or (mytype == "global_mean") or (mytype == "diff_from_mean"):
            logger.info('Intrare în execute_task() cu tipul {mytype} și datele {data}')
            question = data.get('question')
            state_values = {}

            # Variabile necesare pt global_mean
            total_values = 0
            total_entries = 0

            # Se verifică dacă există întrebarea în dicționar și se iterează prin fiecare intrare
            if question in self.data_ingestor.dict:
                for entry in self.data_ingestor.dict[question]:
                    year_start = int(entry["YearStart"])
                    year_end = int(entry["YearEnd"])

                    # Se verifică condițiile cu privire la perioada de timp și la valoarea datelor
                    if 2011 <= year_start <= 2022 and 2011 <= year_end <= 2022 and year_start <= year_end:
                        location = entry["LocationDesc"]
                        if float(entry["Data_Value"]) != 0:

                            # Se rețin valorile indiferent de stat, pt global_mean
                            total_values += float(entry["Data_Value"])
                            total_entries += 1

                            # Se rețin valorile pentru fiecare stat
                            if location not in state_values:
                                state_values[location] = {"sum": 0, "count": 0}
                            state_values[location]["sum"] += float(entry["Data_Value"])
                            state_values[location]["count"] += 1

            # Mediile statelor se rețin în state_means
            state_means = {}
            for location, values in state_values.items():
                state_means[location] = values["sum"] / values["count"]

            # Pentru best5 (best is min) și worst5 (best is max)
            if((question in self.data_ingestor.questions_best_is_min) and (mytype == "best5")) or ((question in self.data_ingestor.questions_best_is_max) and (mytype == "worst5")):
                # Se sortează dict crescător și se extrag 5 medii
                sorted_state_means = dict(sorted(state_means.items(), key=lambda item: item[1]))
                top_5_states = dict(list(sorted_state_means.items())[:5])
                logger.info('Ieșire din execute_task() cu rezultatul {top_5_states}')
                return json.dumps(top_5_states)

            # Pentru best5 (best is max) și worst5 (best is min)
            elif ((question in self.data_ingestor.questions_best_is_max) and (mytype == "best5") ) or ((question in self.data_ingestor.questions_best_is_min) and (mytype == "worst5")):
                # Se sortează dict descrescător și se extrag 5
                sorted_state_means = dict(sorted(state_means.items(), key=lambda item: item[1], reverse=True))
                top_5_states = dict(list(sorted_state_means.items())[:5])
                logger.info('Ieșire din execute_task() cu rezultatul {top_5_states}')
                return json.dumps(top_5_states)

            elif mytype == "states_mean":
                # Doar se sortează dict crescător
                sorted_state_means = dict(sorted(state_means.items(), key=lambda item: item[1]))
                logger.info('Ieșire din execute_task() cu rezultatul {sorted_state_means}')
                return json.dumps(sorted_state_means)

            elif mytype == "global_mean":
                # Se calculează media globală și se returnează
                if total_entries > 0:
                    logger.info('Ieșire din execute_task() cu rezultatul {total_values / total_entries}')
                    return json.dumps({"global_mean": total_values / total_entries})

            elif mytype == "diff_from_mean":
                # Se calculează media globală
                if total_entries > 0:
                    global_mean = total_values / total_entries

                 # Se calculează diferențele dintre media globală și media fiecărui stat
                diff_from_mean = {}
                sorted_state_means = dict(sorted(state_means.items(), key=lambda item: item[1]))
                for location, values in sorted_state_means.items():
                    diff_from_mean[location] = global_mean - values
                logger.info('Ieșire din execute_task() cu rezultatul {diff_from_mean}')
                return json.dumps(diff_from_mean)

        elif mytype == "state_mean" or mytype == "state_diff_from_mean":
            logger.info('Intrare în execute_task() cu tipul {mytype} și datele {data}')
            question = data.get('question')
            state = data.get('state')

            total_values_state_mean = 0
            total_entries_state_mean = 0
            total_values_global_mean = 0
            total_entries_global_mean = 0

            # Se verifică dacă există întrebarea în dicționar și se iterează prin fiecare intrare
            if question in self.data_ingestor.dict:
                for entry in self.data_ingestor.dict[question]:
                    year_start = int(entry["YearStart"])
                    year_end = int(entry["YearEnd"])
                    location = entry["LocationDesc"]

                    # Se verifică condițiile cu privire la perioada de timp și la valoarea datelor
                    if 2011 <= year_start <= 2022 and 2011 <= year_end <= 2022 and year_start <= year_end:

                        if float(entry["Data_Value"]) != 0:
                            # Se rețin valorile indiferent de stat, pt global_mean
                            total_entries_global_mean += 1
                            total_values_global_mean += float(entry["Data_Value"])

                            # Se rețin valorile pt calculul mediei statului dat
                            if location == state:
                                total_values_state_mean += float(entry["Data_Value"])
                                total_entries_state_mean += 1

            # Se calculează media pentru statul dat
            if total_entries_state_mean > 0:
                state_mean = total_values_state_mean / total_entries_state_mean

            if mytype == "state_mean":
                # Se returnează media statului dat
                logger.info('Ieșire din execute_task() cu rezultatul {state_mean}')
                return json.dumps({state : state_mean})

            elif mytype == "state_diff_from_mean":
                # Se calculează media globală și se returnează diferența
                if total_entries_global_mean > 0:
                    global_mean = total_values_global_mean / total_entries_global_mean
                diff_from_mean = global_mean - state_mean
                logger.info('Ieșire din execute_task() cu rezultatul {diff_from_mean}')
                return json.dumps({state : diff_from_mean})

        elif mytype == "mean_by_category":
            logger.info('Intrare în execute_task() cu tipul {mytype} și datele {data}')
            question = data.get('question')
            mean_by_category = {}

            # Se verifică dacă există întrebarea în dicționar și se iterează prin fiecare intrare
            if question in self.data_ingestor.dict:
                for entry in self.data_ingestor.dict[question]:
                    location = entry["LocationDesc"]
                    stratification_category1 = entry["StratificationCategory1"]
                    stratification1 = entry["Stratification1"]
                    data_value = float(entry["Data_Value"])

                    # Se verifică dacă există valori pentru câmpurile necesare
                    if(stratification1 != "" and stratification_category1 != ""):

                        # Se construiește o cheie pentru fiecare stat, stratificare și categoria ei, ce se fol pt a reține datele
                        key = (location, stratification_category1, stratification1)
                        if key not in mean_by_category:
                            mean_by_category [key] = {"sum": 0, "count": 0}
                        mean_by_category [key]["sum"] += data_value
                        mean_by_category [key]["count"] += 1

            json_output = {}
            # Se calculeaza toate mediile, se formatează corespunzător și se returnează ca JSON
            for key, value in mean_by_category .items():
                mean = value["sum"] / value["count"]
                formatted_key = f'(\'{key[0]}\', \'{key[1]}\', \'{key[2]}\')'
                json_output[formatted_key] = mean

            logger.info('Ieșire din execute_task() cu rezultatul {json_output}')
            return json.dumps(json_output)

        elif mytype == "state_mean_by_category":
            logger.info('Intrare în execute_task() cu tipul {mytype} și datele {data}')
            question = data.get('question')
            state = data.get('state')
            state_mean_by_category = {}

            # Se verifică dacă există întrebarea în dicționar și se iterează prin fiecare intrare
            if question in self.data_ingestor.dict:
                for entry in self.data_ingestor.dict[question]:
                    location = entry["LocationDesc"]
                    stratification_category1 = entry["StratificationCategory1"]
                    stratification1 = entry["Stratification1"]
                    data_value = float(entry["Data_Value"])

                    # Se selectează intrările pentru statul dat și cele cu câmpurile nenule
                    if location == state:
                        if (stratification1 != "" and stratification_category1 != ""):

                            # Se construiește o cheie pentru fiecare stratificare și categoria ei, ce se fol pt a reține datele
                            key = (stratification_category1, stratification1)
                            if key not in state_mean_by_category:
                                state_mean_by_category [key] = {"sum": 0, "count": 0}
                            state_mean_by_category [key]["sum"] += data_value
                            state_mean_by_category [key]["count"] += 1

            json_output = {}
            # Se calculeaza toate mediile, se formatează corespunzător răspunsul și se returnează ca JSON
            for key, value in state_mean_by_category .items():
                mean = value["sum"] / value["count"]
                formatted_key = f'(\'{key[0]}\', \'{key[1]}\')'
                json_output[formatted_key] = mean

            logger.info('Ieșire din execute_task() cu rezultatul {json_output}')
            return json.dumps({state : json_output})

            