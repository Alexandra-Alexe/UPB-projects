"""Acest modul definește clasa DataIngestor care se ocupă 
    de încărcarea datelor din fișiere CSV."""
import csv
from app.logging import logger

class DataIngestor:
    """Clasă pentru încărcarea datelor din fișiere CSV."""

    dict = {}

    def load_csv_file(self, file_path):
        """Încarcă datele dintr-un fișier CSV dat de calea `file_path`."""
        logger.info("Se încarcă datele de la calea %s", file_path)
        data = []
        with open(file_path, newline='', encoding='utf-8') as csvfile:
            reader = csv.reader(csvfile)
            for row in reader:
                data.append(row)
        return data


    def __init__(self, csv_path: str):
        # Se citește fișierul CSV și se salvează datele într-o variabilă de instanță
        csv_data = self.load_csv_file(csv_path)
        self.data = csv_data

        # Se extrage capul de tabel
        headers = csv_data[0]

        # Se extrag indecșii coloanelor dorite
        question_index = headers.index("Question")
        data_value_index = headers.index("Data_Value")
        year_start_index = headers.index("YearStart")
        year_end_index = headers.index("YearEnd")
        location_index = headers.index("LocationDesc")
        stratification_category1_index = headers.index("StratificationCategory1")
        stratification1_index = headers.index("Stratification1")
        logger.info("Indecșii coloanelor: %s, %s, %s", question_index, data_value_index,
                    year_start_index)


        # Se iterează prin fiecare linie și se adăugă datele în dicționar
        for row in csv_data[1:]:
            question = row[question_index]
            data_value = row[data_value_index]
            year_start = row[year_start_index]
            year_end = row[year_end_index]
            location = row[location_index]
            stratification_category1 = row[stratification_category1_index]
            stratification1 = row[stratification1_index]

            # Dacă întrebarea există în dicționar,
            # se adaugă o nouă intrare în lista asociată întrebării
            if question in self.dict:
                self.dict[question].append({
                    "Data_Value": data_value,
                    "YearStart": year_start,
                    "YearEnd": year_end,
                    "LocationDesc": location,
                    "StratificationCategory1": stratification_category1,
                    "Stratification1": stratification1
                })
            else:
                # Dacă întrebarea nu există în dicționar,
                # se creează o nouă listă cu o singură intrare
                self.dict[question] = [{
                    "Data_Value": data_value,
                    "YearStart": year_start,
                    "YearEnd": year_end,
                    "LocationDesc": location,
                    "StratificationCategory1": stratification_category1,
                    "Stratification1": stratification1
                }]


        logger.info("Datele au fost încărcate în dicționar")
        self.questions_best_is_min = [
            'Percent of adults aged 18 years and older who have an overweight classification',
            'Percent of adults aged 18 years and older who have obesity',
            'Percent of adults who engage in no leisure-time physical activity',
            'Percent of adults who report consuming fruit less than one time daily',
            'Percent of adults who report consuming vegetables less than one time daily'
        ]

        self.questions_best_is_max = [
            'Percent of adults who achieve at least 150 minutes a week of moderate-intensity aerobic physical activity or 75 minutes a week of vigorous-intensity aerobic activity (or an equivalent combination)',
            'Percent of adults who achieve at least 150 minutes a week of moderate-intensity aerobic physical activity or 75 minutes a week of vigorous-intensity aerobic physical activity and engage in muscle-strengthening activities on 2 or more days a week',
            'Percent of adults who achieve at least 300 minutes a week of moderate-intensity aerobic physical activity or 150 minutes a week of vigorous-intensity aerobic activity (or an equivalent combination)',
            'Percent of adults who engage in muscle-strengthening activities on 2 or more days a week',
        ]
