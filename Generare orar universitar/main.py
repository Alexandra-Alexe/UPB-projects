import random
from typing import Dict, List, Tuple
import numpy as np
import yaml
from arhiva import utils


class State:
    def __init__(
        self,
        schedule: Dict[str, Dict[Tuple[int, int], List[Tuple[str, str, str, int]]]] | None = None, 
        dict_subjects: Dict[str, int] | None = None,
        dict_teachers: Dict[str, Tuple[List[str], List[str]]] | None = None,
        dict_rooms: Dict[str, Tuple[int, List[str]]] | None = None
        # conflicts: int | None = None
    ) -> None:
        # self.nconflicts = conflicts if conflicts is not None else State.__compute_conflicts(self.size, self.board)
        self.dict_subjects = dict_subjects if dict_subjects is not None else self.generate_dict_subjects()
        self.dict_techers = dict_teachers if dict_teachers is not None else self.generate_dict_teachers()
        self.dict_rooms = dict_rooms if dict_rooms is not None else self.generate_dict_rooms()
        self.schedule = schedule if schedule is not None else State.generate_schedule()

    def apply_move(self) -> 'State':
        '''
        Construiește o stare vecină în care se încearcă o schimbare mai bună.
        '''
        new_schedule = self.schedule.copy()
        for subject, stud_no in self.dict_subjects.items():
            print(subject, stud_no)
            if(stud_no != 0):
                pass

        return State(new_schedule)

    @staticmethod
    def generate_dict_rooms() -> Dict[str, Tuple[int, List[str]]]:
        '''
        Construiește un dicționar pentru a ține evidența sălilor, capacitățile lor și materiile asociate.
        '''
        dict_rooms = {}

        # Deschide fișierul YAML și citeste datele
        with open('arhiva/inputs/dummy.yaml', 'r') as file:
            data = yaml.safe_load(file)

        # Iterează prin fiecare sală și detalii despre aceasta din datele citite
        for room, detalii_sala in data['Sali'].items():
            capacity = detalii_sala['Capacitate']
            subjects = detalii_sala['Materii']
            dict_rooms[room] = (capacity, subjects)

        return dict_rooms

    @staticmethod
    def generate_dict_teachers() -> Dict[str, Tuple[List[str], List[str]]]:
        '''
        Construiește un dicționar pentru a ține evidența profesorilor, constrângerile de program și materiile pe care le predau.
        '''
        dict_teachers = {}

        # Deschide fișierul YAML și citeste datele
        with open('arhiva/inputs/dummy.yaml', 'r') as file:
            data = yaml.safe_load(file)

        # Iterează prin fiecare profesor și materie din datele citite
        for teacher, details in data['Profesori'].items():
            subjects = details['Materii']
            constraints = details['Constrangeri']
            dict_teachers[teacher] = (subjects, constraints)

        return dict_teachers

    @staticmethod
    def generate_dict_subjects() -> Dict[str, int]:
        '''
        Construiește un dicționar pentru a ține evidența materiilor și a numărului de studenți.
        '''
        dict_subjects = {}

        # Deschide fișierul YAML și citeste datele
        with open('arhiva/inputs/dummy.yaml', 'r') as file:
            data = yaml.safe_load(file)

        for subject, stud_no in data['Materii'].items():
            dict_subjects[subject] = stud_no

        return dict_subjects

    @staticmethod
    def generate_schedule() -> Dict[str, Dict[Tuple[int, int], List[Tuple[str, str, str, int]]]]:
        '''
        Construiește un dicționar de dicționare pentru programul de cursuri, care initial e gol.
        '''
        schedule = {}

        # Deschide fișierul YAML și citeste datele
        data = utils.read_yaml_file('arhiva/inputs/dummy.yaml')

        #iau fiecare zi la rand
        for day in data['Zile']:
            schedule[day] = {}

            #iau fiecare interval la rand
            for interval in data['Intervale']:
                # Initializeaza lista de sali pentru acest interval
                rooms = []

                #iau fiecare sala la rand
                for room in data['Sali']:

                    # caut materie pt sala room care mai are stundeti neasezati
                    subject = None
                    for subject in data['Sali'][room]['Materii']:
                        if data['Materii'][subject] >= 0:

                            # nr de stud e mai mare decat permite sala
                            if data['Materii'][subject] > data['Sali'][room]['Capacitate']:
                                stud_no = data['Sali'][room]['Capacitate']
                                data['Materii'][subject] = data['Materii'][subject] - stud_no
                            
                            else:
                                stud_no = data['Materii'][subject]
                                data['Materii'][subject] = 0
                            
                            teacher_list = [profesor for profesor, info_profesor in data['Profesori'].items() if subject in info_profesor['Materii']]
                            teacher_chosen = random.choice(teacher_list)

                        else:
                            break
                    
                    # stabilesc tuplul si il pun in lista de sali
                    if subject is not None:
                        tuplu_sala = (
                            room,
                            subject,
                            teacher_chosen,
                            stud_no
                        )
                        rooms.append(tuplu_sala)
                    else:
                        print(" toate materiile corespunzatoare acestei sali s-au completat")
                        rooms.append((room, None, None, 0)) # toate materiile corespunzatoare acestei sali s-au completat
                
                schedule[day][interval] = rooms

        return schedule
    


    def display_schedule(self) -> None:
        for day, intervals in self.schedule.items():
            print(day + ":")
            for interval, rooms in intervals.items():
                print(f"    {interval}:")
                for room in rooms:
                    print(f"        Sala: {room[0]}, Materie: {room[1]}, Profesor: {room[2]}, Nr. de studenți: {room[3]}")
    


mystate = State()
mystate.display_schedule()