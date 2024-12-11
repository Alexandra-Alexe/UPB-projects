"""Acest modul definește rutele pentru webserver."""
import os
import json
import time
from flask import request, jsonify
from app import webserver
from app.logging import logger

@webserver.route('/api/get_results/<job_id>', methods=['GET'])
def get_response(job_id):
    """Verifică corectitudinea răspunsului pentru request."""
    if request.method == 'GET':
        logger.info('Intrare în ruta /api/get_results cu parametrul: {job_id}')
        # Se verifică daca procesarea job-ului s-a terminat
        if webserver.thread_pool.pairs[job_id] == "done":
            result_path = f"./app/results/{job_id}.json"
            # Se verifică dacă fișierul rezultat există
            if os.path.exists(result_path):
                with open(result_path, 'r', encoding='utf-8') as file:
                    # Se încarcă datele și se incrementează numărul de job-uri terminate
                    try:
                        data = json.load(file)
                        webserver.thread_pool.finished_jobs += 1
                        logger.info('Iesire din ruta /api/get_results cu statusul "done" si parametrul: {data} pentru {job_id}')
                        return jsonify ({ "status": "done", "data": data }), 200
                    except json.JSONDecodeError:
                        # Cazul în care fișierul rezultat este gol
                        logger.error('Eroare: Fișierul rezultat este gol - {result_path}')
                        return jsonify({"status": "error", "reason": "reading from file"}), 500
            else:
                # Cazul în care fișierul rezultat nu există
                logger.error('Eroare: Fișierul rezultat nu există - {result_path}')
                return jsonify({"status": "error", "reason": "file not found"}), 404
        # Cazul în care job-ul este în curs de procesare
        elif webserver.thread_pool.pairs[job_id] == "running":
            logger.info('Iesire din ruta /api.get_results cu statusul "running" pentru  {job_id}')
            return jsonify({"status": "running"}), 200
    # Metoda neacceptată
    logger.error('Eroare: Metodă neacceptată în /api/get_results - {request.method}')
    return jsonify({"error": "Method not allowed"}), 405


@webserver.route('/api/states_mean', methods=['POST'])
def states_mean_request():
    """Procesează request-ul pentru a calcula media pentru fiecare stat."""
    if request.method == 'POST':
        data = request.json
        logger.info('Intrare în ruta /api/states_mean cu parametrul: {data}')

        # Se incrementează counter-ul de job-uri
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.job_id_counter += 1
            current_job_id = webserver.thread_pool.job_id_counter

        # Se memorează tipul de request, id-ul atribuit și datele primite în tuplul job_data
        mytype = "states_mean"
        job_data = (mytype, current_job_id, data)

        # Se reține statusul job-ului
        status = "running"

        # Se adaugă tuplul în coadă și se adaugă perechea job_id - status în dicționar
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.queue.put(job_data)
            webserver.thread_pool.pairs["job_id_" + str(current_job_id)] = status

        logger.info('Iesire în ruta /api/states_mean cu parametrul: job_id_{current_job_id}')
        return jsonify({"job_id": "job_id_" + str(current_job_id)})
    else:
        # Metoda neacceptată
        logger.error('Eroare: Metodă neacceptată în /api/states_mean - {request.method}')
        return jsonify({"error": "Method not allowed"}), 405

@webserver.route('/api/state_mean', methods=['POST'])
def state_mean_request():
    """Procesează request-ul pentru a calcula media pentru un stat dat."""
    if request.method == 'POST':
        data = request.json
        logger.info('Intrare în ruta /api/state_mean cu parametrul: {data}')

        # Se incrementează counter-ul de job-uri
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.job_id_counter += 1
            current_job_id = webserver.thread_pool.job_id_counter

        # Se memorează tipul de request, id-ul atribuit și datele primite în tuplul job_data
        mytype = "state_mean"
        job_data = (mytype, current_job_id, data)

        # Se reține statusul job-uluiS
        status = "running"

        # Se adaugă tuplul în coadă și se adaugă perechea job_id - status în dicționar
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.pairs["job_id_" + str(current_job_id)] = status
            webserver.thread_pool.queue.put(job_data)

        logger.info('Iesire în ruta /api/state_mean cu parametrul: job_id_{current_job_id}')
        return jsonify({"job_id": "job_id_" + str(current_job_id)})
    else:
        # Metoda neacceptată
        logger.error('Eroare: Metodă neacceptată în /api/state_mean - {request.method}')
        return jsonify({"error": "Method not allowed"}), 405



@webserver.route('/api/best5', methods=['POST'])
def best5_request():
    """Procesează request-ul pentru a calcula cele mai bune 5 state."""
    if request.method == 'POST':
        data = request.json
        logger.info('Intrare în ruta /api/best5 cu parametrul: {data}')

        # Se incrementează counter-ul de job-uri
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.job_id_counter += 1
            current_job_id = webserver.thread_pool.job_id_counter

        # Se memorează tipul de request, id-ul atribuit și datele primite în tuplul job_data
        mytype = "best5"
        job_data = (mytype, current_job_id, data)

        # Se reține statusul job-ului
        status = "running"

        # Se adaugă tuplul în coadă și se adaugă perechea job_id - status în dicționar
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.pairs["job_id_" + str(current_job_id)] = status
            webserver.thread_pool.queue.put(job_data)

        logger.info('Iesire în ruta /api/best5 cu parametrul: job_id_{current_job_id}')
        return jsonify({"job_id": "job_id_" + str(current_job_id)})
    else:
        # Metoda neacceptată
        logger.error('Eroare: Metodă neacceptată în /api/best5 - {request.method}')
        return jsonify({"error": "Method not allowed"}), 405

@webserver.route('/api/worst5', methods=['POST'])
def worst5_request():
    """Procesează request-ul pentru a calcula cele mai slabe 5 state."""
    if request.method == 'POST':
        data = request.json
        logger.info('Intrare în ruta /api/worst5 cu parametrul: {data}')

        # Se incrementează counter-ul de job-uri
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.job_id_counter += 1
            current_job_id = webserver.thread_pool.job_id_counter

        # Se memorează tipul de request, id-ul atribuit și datele primite în tuplul job_data
        mytype = "worst5"
        job_data = (mytype, current_job_id, data)

        # Se reține statusul job-ului
        status = "running"

        # Se adaugă tuplul în coadă și se adaugă perechea job_id - status în dicționar
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.pairs["job_id_" + str(current_job_id)] = status
            webserver.thread_pool.queue.put(job_data)

        logger.info('Iesire în ruta /api/worst5 cu parametrul: job_id_{current_job_id}')
        return jsonify({"job_id": "job_id_" + str(current_job_id)})
    else:
        # Metoda neacceptată
        logger.error('Eroare: Metodă neacceptată în /api/worst5 - {request.method}')
        return jsonify({"error": "Method not allowed"}), 405


@webserver.route('/api/global_mean', methods=['POST'])
def global_mean_request():
    """Procesează request-ul pentru a calcula media globală."""
    if request.method == 'POST':
        data = request.json
        logger.info('Intrare în ruta /api/global_mean cu parametrul: {data}')

        # Se incrementează counter-ul de job-uri
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.job_id_counter += 1
            current_job_id = webserver.thread_pool.job_id_counter

        # Se memorează tipul de request, id-ul atribuit și datele primite în tuplul job_data
        mytype = "global_mean"
        job_data = (mytype, current_job_id, data)

        # Se reține statusul job-ului
        status = "running"

        # Se adaugă tuplul în coadă și se adaugă perechea job_id - status în dicționar
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.pairs["job_id_" + str(current_job_id)] = status
            webserver.thread_pool.queue.put(job_data)

        logger.info('Iesire în ruta /api/global_mean cu parametrul: job_id_{current_job_id}')
        return jsonify({"job_id": "job_id_" + str(current_job_id)})
    else:
        # Metoda neacceptată
        logger.error('Eroare: Metodă neacceptată în /api/global_mean - {request.method}')
        return jsonify({"error": "Method not allowed"}), 405

@webserver.route('/api/diff_from_mean', methods=['POST'])
def diff_from_mean_request():
    """Procesează request-ul pentru a calcula diferența statelor față de media globală."""
    if request.method == 'POST':
        data = request.json
        logger.info('Intrare în ruta /api/diff_from_mean cu parametrul: {data}')

        # Se incrementează counter-ul de job-uri
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.job_id_counter += 1
            current_job_id = webserver.thread_pool.job_id_counter

        # Se memorează tipul de request, id-ul atribuit și datele primite în tuplul job_data
        mytype = "diff_from_mean"
        job_data = (mytype, current_job_id, data)

        # Se reține statusul job-ului
        status = "running"

        # Se adaugă tuplul în coadă și se adaugă perechea job_id - status în dicționar
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.pairs["job_id_" + str(current_job_id)] = status
            webserver.thread_pool.queue.put(job_data)

        logger.info('Iesire în ruta /api/diff_from_mean cu parametrul: job_id_{current_job_id}')
        return jsonify({"job_id": "job_id_" + str(current_job_id)})
    else:
        # Metoda neacceptată
        logger.error('Eroare: Metodă neacceptată în /api/diff_from_mean - {request.method}')
        return jsonify({"error": "Method not allowed"}), 405

@webserver.route('/api/state_diff_from_mean', methods=['POST'])
def state_diff_from_mean_request():
    """Procesează request-ul pentru a calcula diferența față de media globală si statul dat."""
    if request.method == 'POST':
        data = request.json
        logger.info('Intrare în ruta /api/state_diff_from_mean cu parametrul: {data}')

        # Se incrementează counter-ul de job-uri
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.job_id_counter += 1
            current_job_id = webserver.thread_pool.job_id_counter

        # Se memorează tipul de request, id-ul atribuit și datele primite în tuplul job_data
        mytype = "state_diff_from_mean"
        job_data = (mytype, current_job_id, data)

        # Se reține statusul job-ului
        status = "running"

        # Se adaugă tuplul în coadă și se adaugă perechea job_id - status în dicționar
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.pairs["job_id_" + str(current_job_id)] = status
            webserver.thread_pool.queue.put(job_data)

        logger.info('Iesire în ruta /api/state_diff_from_mean cu parametrul:job_id_{current_job_id}')
        return jsonify({"job_id": "job_id_" + str(current_job_id)})
    else:
        # Metoda neacceptată
        logger.error('Eroare: Metodă neacceptată în /api/state_diff_from_mean - {request.method}')
        return jsonify({"error": "Method not allowed"}), 405

@webserver.route('/api/mean_by_category', methods=['POST'])
def mean_by_category_request():
    """Procesează request-ul pentru a calcula media pentru fiecare categorie."""
    if request.method == 'POST':
        data = request.json
        logger.info('Intrare în ruta /api/mean_by_category cu parametrul: {data}')

        # Se incrementează counter-ul de job-uri
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.job_id_counter += 1
            current_job_id = webserver.thread_pool.job_id_counter

        # Se memorează tipul de request, id-ul atribuit și datele primite în tuplul job_data
        mytype = "mean_by_category"
        job_data = (mytype, current_job_id, data)

        # Se reține statusul job-ului
        status = "running"

        # Se adaugă tuplul în coadă și se adaugă perechea job_id - status în dicționar
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.pairs["job_id_" + str(current_job_id)] = status
            webserver.thread_pool.queue.put(job_data)

        logger.info('Iesire în ruta /api/mean_by_category cu parametrul: job_id_{current_job_id}')
        return jsonify({"job_id": "job_id_" + str(current_job_id)})
    else:
        # Metoda neacceptată
        logger.error('Eroare: Metodă neacceptată în /api/mean_by_category - {request.method}')
        return jsonify({"error": "Method not allowed"}), 405

@webserver.route('/api/state_mean_by_category', methods=['POST'])
def state_mean_by_category_request():
    """Procesează request-ul pentru a calcula media pentru fiecare stat și categorie."""
    if request.method == 'POST':
        data = request.json
        logger.info('Intrare în ruta /api/state_mean_by_category cu parametrul: {data}')

        # Se incrementează counter-ul de job-uri
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.job_id_counter += 1
            current_job_id = webserver.thread_pool.job_id_counter

        # Se memorează tipul de request, id-ul atribuit și datele primite în tuplul job_data
        mytype = "state_mean_by_category"
        job_data = (mytype, current_job_id, data)

        # Se reține statusul job-ului
        status = "running"

        # Se adaugă tuplul în coadă și se adaugă perechea job_id - status în dicționar
        with webserver.thread_pool.my_lock:
            webserver.thread_pool.pairs["job_id_" + str(current_job_id)] = status
            webserver.thread_pool.queue.put(job_data)

        logger.info('Iesire în ruta /api/state_mean_by_category cu parametrul: job_id_{current_job_id}')
        return jsonify({"job_id": "job_id_" + str(current_job_id)})
    else:
        logger.error('Eroare: Metodă neacceptată în /api/state_mean_by_category - {request.method}')
        return jsonify({"error": "Method not allowed"}), 405

@webserver.route('/api/graceful_shutdown', methods=['GET'])
def graceful_shutdown():
    """Inițiază shutdown-ul serverului."""
    logger.info('Intrare în ruta /api/graceful_shutdown cu parametrul shutdown_flag - {webserver.thread_pool.shutdown_flag}')
    # Se verifică dacă toate job-urile au fost terminate
    if webserver.thread_pool.finished_jobs == webserver.thread_pool.job_id_counter:
        for thread in webserver.thread_pool.pool:
            thread.join()

        # Se setează flag-ul de shutdown
        webserver.thread_pool.graceful_shutdown_flag = True
        logger.info('Iesire în ruta /api/graceful_shutdown cu parametrul shutdown_flag - {webserver.thread_pool.shutdown_flag}')
        return jsonify({"message": "Graceful shutdown initiated."})


@webserver.route('/api/num_jobs', methods=['GET'])
def num_jobs():
    """Returnează numărul de job-uri care sunt în curs de procesare."""
    logger.info('Intrare în ruta /api/num_jobs')
    # Se verifică dacă flag-ul de shutdown a fost setat, caz în care se returnează 0
    if webserver.thread_pool.graceful_shutdown_flag:
        time.sleep(10)
        logger.info('Iesire în ruta /api/num_jobs cu parametrul num_jobs - 0')
        return jsonify({"num_jobs": 0})
    else:
        no = webserver.thread_pool.job_id_counter - webserver.thread_pool.finished_jobs
        logger.info('Iesire în ruta /api/num_jobs cu parametrul num_jobs - {no}')
        return jsonify({"num_jobs": no})

@webserver.route('/api/jobs', methods=['GET'])
def jobs():
    # Se returnează statusul fiecărui job folosing dicționarul cu perechi job_id - status
    logger.info('Intrare în ruta /api/jobs')
    return jsonify({"status": "done", "data": webserver.thread_pool.pairs})


# You can check localhost in your browser to see what this displays
@webserver.route('/')
@webserver.route('/index')
def index():
    routes = get_defined_routes()
    msg = "Hello, World!\n Interact with the webserver using one of the defined routes:\n"

    # Display each route as a separate HTML <p> tag
    paragraphs = ""
    for route in routes:
        paragraphs += f"<p>{route}</p>"

    msg += paragraphs
    return msg

def get_defined_routes():
    routes = []
    for rule in webserver.url_map.iter_rules():
        methods = ', '.join(rule.methods)
        routes.append(f"Endpoint: \"{rule}\" Methods: \"{methods}\"")
    return routes
