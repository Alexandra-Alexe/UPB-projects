"""Acest modul configureaza un obiect logger pentru a scrie în fișierul 
webserver.log"""
import os
import logging
from logging.handlers import RotatingFileHandler


# Directorul în care se vor stoca fișierele de log
LOG_DIR = './app/'

def get_next_log_filename():
    """Returnează numele fișierului de log următor."""
    log_filename = 'webserver.log'
    return os.path.join(LOG_DIR, log_filename)

def find_next_available_log_filename():
    """Returnează următorul nume de fișier de log disponibil."""
    suffix = 0
    while True:
        file_name = get_next_log_filename() + (f'.{suffix}' if suffix > 0 else '')
        if not os.path.exists(file_name):
            return file_name
        suffix += 1

# Crearea unui obiect logger
logger = logging.getLogger('webserver')
logger.setLevel(logging.INFO)

MAX_FILE_SIZE = 100 * 1024 * 1024
BACKUP_COUNT = 10

handler = RotatingFileHandler(find_next_available_log_filename(), mode='a',
                              maxBytes=MAX_FILE_SIZE, backupCount=BACKUP_COUNT)

# Setarea formatului pentru handler
formatter = logging.Formatter('%(asctime)s - %(levelname)s - %(message)s',
                              datefmt='%Y-%m-%d %H:%M:%S')
handler.setFormatter(formatter)

# Adăugarea handler-ului la logger
logger.addHandler(handler)
