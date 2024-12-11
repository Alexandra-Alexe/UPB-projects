"""Modulul de inițializare pentru tema."""
from flask import Flask
from app.task_runner import ThreadPool
from app.logging import logger

logger.info('Starting webserver')
webserver = Flask(__name__)
webserver.thread_pool = ThreadPool()


from app import routes
