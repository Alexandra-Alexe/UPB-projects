from copy import deepcopy
import random
from typing import Dict, List, Tuple
import yaml

class State:
    def __init__(
        self,
        input_path: str | None = None,
        schedule: Dict[str, Dict[Tuple[int, int], List[Tuple[str, str, str, int]]]] | None = None,
        dict_teachers_fav: Dict[str, Tuple[List[str], List[str]]] | None = None,
        dict_rooms: Dict[str, Tuple[int, List[str]]] | None = None,
        dict_subjects: Dict[str, int] | None = None
    ) -> None:
        self.input_path = input_path
        self.dict_subjects = dict_subjects if dict_subjects is not None else self.generate_dict_subjects(input_path)
        self.dict_teachers_fav = dict_teachers_fav if dict_teachers_fav is not None else State.generate_dict_teachers_fav(input_path)
        self.dict_rooms = dict_rooms if dict_rooms is not None else self.generate_dict_rooms(input_path)
        self.schedule = schedule if schedule is not None else State.generate_schedule(input_path)

    @staticmethod
    def generate_dict_subjects(input_path: str) -> Dict[str, int]:
        '''
        Construiește un dicționar pentru a ține evidența materiilor și a numărului de studenți.
        '''
        dict_subjects = {}

        # se deschide fișierul, se citesc datele si se stocheaza in dict_subjects
        with open(input_path, 'r') as file:
            data = yaml.safe_load(file)

        for subject, stud_no in data['Materii'].items():
            dict_subjects[subject] = stud_no

        return dict_subjects

    @staticmethod
    def generate_dict_teachers_fav(input_path : str) -> Dict[str, Tuple[List[str], List[str]]]:
        '''
        Selecteaza preferintele profesorilor pentru zile si intervale intr-un dictionar.
        '''

        dict_teachers = {}

        # se deschide fișierul și se citesc datele
        with open(input_path, 'r') as file:
            data = yaml.safe_load(file)

        # se iterează prin lista de profesori
        for teacher, details in data['Profesori'].items():
            constraints = details['Constrangeri']
            preferred_days = []
            preferred_intervals = []

            for constraint in constraints:
                # se retin in preferred_days zilele preferate de profesor
                if constraint[0] != '!' and not '-' in constraint:
                    preferred_days.append(constraint)
                # se retin in preferred_intervals intervalele preferate de profesor
                elif constraint[0] != '!' and '-' in constraint:
                    start_str, end_str = constraint.split('-')
                    start_int = int(start_str)
                    end_int = int(end_str)
                    while end_int - start_int != 2:
                        preferred_intervals.append((start_int, start_int + 2))
                        start_int += 2
                    preferred_intervals.append((start_int, end_int))
            # se formeaza un tuplu din zilele, intervalele preferate si materii, care se adauga in dictionarul dict_teachers
            dict_teachers[teacher] = (preferred_days, preferred_intervals, details['Materii'])
        return dict_teachers
    
    @staticmethod
    def generate_dict_rooms(input_path : str) -> Dict[str, Tuple[int, List[str]]]:
        '''
        Construiește un dicționar pentru a ține evidența sălilor, capacitățile lor și materiile asociate.
        '''
        dict_rooms = {}

        # se deschide fișierul și se citesc datele
        with open(input_path, 'r') as file:
            data = yaml.safe_load(file)

        # se itereaza prin lista de sali și retin in dictionar capacitatea si materiile sub forma de tuplu
        for room, detalii_sala in data['Sali'].items():
            capacity = detalii_sala['Capacitate']
            subjects = detalii_sala['Materii']
            dict_rooms[room] = (capacity, subjects)
        return dict_rooms

    @staticmethod
    def generate_schedule(input_path : str) -> Dict[str, Dict[Tuple[int, int], List[Tuple[str, str, str, int]]]]:
        '''
        Construieste o stare initiala a orarului, care sa respecte constrangerile hard    
        '''

        schedule = {}
        with open(input_path, 'r') as file:
            data = yaml.safe_load(file)

        # dictionar prin care ma asigur ca un profesor nu preda in mai mult de 7 intervale pe saptamana
        max7_teacher_list = {}
        for profesor in data['Profesori']:
            max7_teacher_list[profesor] = 0


        for day in data['Zile']:
            schedule[day] = {}

            for interval in data['Intervale']:
                rooms = {}

                teacher_list = deepcopy(data['Profesori'])
                for teacher in data['Profesori']:
                    if max7_teacher_list[teacher] == 7:
                                teacher_list.pop(teacher)

                for room in data['Sali']:
                    subject = None
                    for subject in data['Sali'][room]['Materii']:
                        stud_no = 0

                        if data['Materii'][subject] > 0:

                            # verificarea numarul de studenti cu dimensiunea salii
                            if data['Materii'][subject] > data['Sali'][room]['Capacitate']:
                                stud_no = data['Sali'][room]['Capacitate']
                                data['Materii'][subject] = data['Materii'][subject] - stud_no
                            
                            else:
                                stud_no = data['Materii'][subject]
                                data['Materii'][subject] = 0
                            
                            # selectarea profesorilor care predau acea materie
                            new_teacher_list = [profesor for profesor, info_profesor in teacher_list.items() if subject in info_profesor['Materii']]
                            
                            # din lista de profesori, sunt selectati primii cei care prefera acel interval si acea zi
                            # de asemenea, au prioritatea in alegere, profesorii care predau un numar mic de materii
                            teacher_chosen = ""
                            dim_min = 100
                            for t in new_teacher_list:
                                if day in data['Profesori'][t]['Constrangeri'] and not day.startswith('!') and interval in data['Profesori'][t]['Constrangeri'] and not interval.startswith('!'):
                                    dim = len(data['Profesori'][t]['Materii'])
                                    if dim == 1:
                                        teacher_chosen = t
                                        break
                                    elif dim < dim_min:
                                        teacher_chosen = t
                                        dim_min = dim

                            # daca nu este cazul, profesorul se alege random
                            if teacher_chosen == "" and len(new_teacher_list) > 0:
                                teacher_chosen = random.choice(new_teacher_list)
                            else:
                                teacher_chosen = random.choice(list(profesor for profesor, info_profesor in teacher_list.items()))

                            # se elimina profesorul ales din lista si se incrementeaza numarul de cursuri predate
                            teacher_list.pop(teacher_chosen)
                            max7_teacher_list[teacher_chosen] += 1
                            break
                    
                    # se stabileste profesorul si materia si se asociaza cu sala
                    if subject is not None and stud_no > 0:
                        tuplu_sala = (
                            teacher_chosen,
                            subject
                        )
                        rooms[room] = tuplu_sala
                    else:
                        # sala ramane goala daca toate materiile corespunzatoare ei, s-au completat
                        rooms[room] = None

                # se asociaza zilei si intervalului, lista de sali
                interval_tuple = eval(interval)
                schedule[day][interval_tuple] = rooms
                
        return schedule
    

    def get_next_states(self) -> list['State']:
        '''
        Functia primeste o stare data si dictionarele cu informatii despre profesori si sali de care se foloseste in prelucrare.
        Este returnata o lista de tupluri care contin mai multe informatii necesare in executia unei actiuni.
        '''
        next_states = []
        # dictionar pentru stocarea salilor goale 
        empty_rooms = {}
        # dictionar pentru stocarea profesorilor nemultumiti de zi / interval
        unhappy_teachers = {}
        # dictionar pentru stocarea profesorilor care nu si-au facut maximul de ore pe saptamana
        max7_teacher_list = {}

        # se parcurge intreg dictionarul
        for day in self.schedule.keys():
            for interval in self.schedule[day].keys():
                for room in self.schedule[day][interval]:

                    if self.schedule[day][interval][room] is not None:
                        teacher, subject = self.schedule[day][interval][room]

                        # se retine numarul de ore predate de fiecare profesor
                        if teacher in max7_teacher_list.keys():
                            max7_teacher_list[teacher] = max7_teacher_list[teacher] + 1
                        else:
                            max7_teacher_list[teacher] = 1

                        preferred_days, preferred_intervals, subjects = self.dict_teachers_fav[teacher]

                        # daca ziua sau intervalul nu sunt preferate de profesor, se retine in dictionarul unhappy_teachers pentru ca ulterior sa poate construi o noua stare
                        if day in preferred_days and interval in preferred_intervals:
                            pass
                        else:
                            unhappy_teachers[teacher] = (preferred_days, preferred_intervals, day, interval, room, subject)
                    else:
                        # se retin salile goale
                        empty_rooms[room] = (day, interval) # ma fol de dict_room pt a verifica mai tarziu ca materia si nr de stud sa corespunda


        # se cauta actiunile posibile pentru a il face fericit pe profesor
        for teacher in unhappy_teachers.keys():
            # pentru fiecare profesor nemultumit, se retin informatiile despre zi, interval, sala, materie si preferintele de zile si intervale
            preferred_days, preferred_intervals, unhappy_day, unhappy_interval, teacher_room, subject = unhappy_teachers[teacher]
            # se creeaza o lista de profesori care nu au posibilitatea sa il inlocuiasca, avand acelasi slot orar
            list_teachers_on_that_interval = list(set([self.schedule[unhappy_day][unhappy_interval][room][0] for room in self.schedule[unhappy_day][unhappy_interval] if self.schedule[unhappy_day][unhappy_interval][room]])) 

            # cazul 1: se cauta o sala goala
            for e_room in empty_rooms:
                day, interval = empty_rooms[e_room]

                ''' 
                Daca ziua si intervalul in care sala e elibera sunt preferate de profesor,
                daca materia predata de profesor e printre materiile salii libere,
                daca capacitatea salii libere e mai mare sau egala cu capacitatea fostei sali
                atunci s-a gasit o sala goala.
                '''
                if day in preferred_days and interval in preferred_intervals and subject in self.dict_rooms[e_room][1] and self.dict_rooms[e_room][0] >= self.dict_rooms[teacher_room][0]:
                    new_state = self.apply_move("move_to_empty_room", teacher, unhappy_day, unhappy_interval, teacher_room, subject,
                                                None, day, interval, e_room, None)
                    next_states.append(new_state)
            
            # cazul 2: inlocuiesc profesorul
            for teacher2 in max7_teacher_list.keys():
                no_max7 = max7_teacher_list[teacher2]
                subject2 = self.dict_teachers_fav[teacher2][2]
                
                # consider profesorii care nu si-au facut maximul de ore pe saptamana si care predau aceeasi materie ca profesorul nemultumit
                if no_max7 < 7 and subject in subject2 and teacher2 not in list_teachers_on_that_interval:
                    preferred_days2, preferred_intervals2, subjects = self.dict_teachers_fav[teacher2]

                    # daca acest profesor prefera ziua si intervalul in care profesorul nemultumit preda, se face schimbarea
                    if unhappy_day in preferred_days2 and unhappy_interval in preferred_intervals2:
                        new_state = self.apply_move("new_teacher", teacher, unhappy_day, unhappy_interval, teacher_room, subject,
                                                     teacher2, None, None, None, subject2) 
                        next_states.append(new_state)
            
            # cazul 3: schimb cu un alt profesor
            for day2 in preferred_days:
                for interval2 in preferred_intervals:
                    for room2 in self.schedule[day2][interval2]:
                        if self.schedule[day2][interval2][room2] is not None:

                            teacher2, subject2 = self.schedule[day2][interval2][room2]
                            # profesorul ales nu trebuie sa predea in acelasi interval, in aceeasi zi
                            if teacher2 not in list_teachers_on_that_interval:
                                """
                                Daca materia predata de profesorul nemultumit se poate preda in sala in care vreau sa fac schimbul si viceversa
                                si daca capacitatile salilor sunt egale, atunci se poate face schimbul.
                                """
                                if subject in self.dict_rooms[room2][1] and subject2 in self.dict_rooms[teacher_room][1] and self.dict_rooms[teacher_room][0] == self.dict_rooms[room2][0]:
                                    new_state = self.apply_move("switch", teacher, unhappy_day, unhappy_interval, teacher_room, subject,
                                                        teacher2, day2, interval2, room2, subject2) 
                                    next_states.append(new_state)
        return next_states
     

    def apply_move(self, thetype: str, teacher1: str, day1: str, interval1: Tuple[int, int], room1: str, subject1: str,
                    teacher2: str, day2: str, interval2: Tuple[int, int], room2: str, subject2: str) -> 'State':
        
        new_schedule = deepcopy(self.schedule)
        # in functie de tipul mutarii, se face schimbarea pe o copie a orarului
        if thetype == "move_to_empty_room":
            new_schedule[day1][interval1][room1] = None
            new_schedule[day2][interval2][room2] = (teacher1, subject1)
        elif thetype == "switch":
            new_schedule[day1][interval1][room1] = None
            new_schedule[day1][interval1][room1] = (teacher2, subject2)
            new_schedule[day2][interval2][room2] = None
            new_schedule[day2][interval2][room2] = (teacher1, subject1)
        elif thetype == "new_teacher":
            new_schedule[day1][interval1][room1] = None
            new_schedule[day1][interval1][room1] = (teacher2, subject1)

        # se creeaza o noua stare folosind orarul modificat
        s =  State(self.input_path ,new_schedule, self.dict_teachers_fav, self.dict_rooms, self.dict_subjects)
        return s

    def conflicts(self) -> int:
        '''
        Functia primeste o stare si dictionarele cu informatii despre materii, profesori si sali.
        Se returneaza numarul de conflicte gasite in acea stare.
        '''
        no_conflicts = 0
        acoperire_reala = {subject : 0 for subject in self.dict_subjects.keys()}
        max7_teacher_list = {}
        
        for day in self.schedule.keys():
            for interval in self.schedule[day].keys():
                techer_list = []
                for room in self.schedule[day][interval]:

                    if self.schedule[day][interval][room] is not None:
                        teacher, subject = self.schedule[day][interval][room]
                       
                        # in dictionarul acoperire_reala se retine numarul de studenti care urmeaza cursul fiecarei materii
                        acoperire_reala[subject] += self.dict_rooms[room][0]
                        
                        # cu ajutorul dict max7_teacher_list ma asigur ca un profesor nu preda in mai mult 7 intervale pe saptamana
                        if teacher in max7_teacher_list.keys():
                            max7_teacher_list[teacher] = max7_teacher_list[teacher] + 1
                        else:
                            max7_teacher_list[teacher] = 1

                        # cazul in care un preofesor preda de doua ori in acelasi interval
                        if teacher in techer_list:
                            no_conflicts += 1
                        else:
                            techer_list.append(teacher)

                        # cazul in care materia nu este corespunzatoare salii
                        if subject not in self.dict_rooms[room][1]:
                            no_conflicts += 1
                            
                        # cazul in care un profesor preda o materie pe care nu o cunoaste
                        if subject not in self.dict_teachers_fav[teacher][2]:
                            no_conflicts += 1
                            
                        # cazul in care profesorul nu prefera acea zi
                        if day not in self.dict_teachers_fav[teacher][0]:
                            no_conflicts += 1
                            
                        # cazul in care proefesorul nu prefera acel interval
                        if interval not in self.dict_teachers_fav[teacher][1]:
                            no_conflicts += 1

        # cazul in care materia nu este acoperita de numarul de studenti necesar
        for subject, target_coverage in self.dict_subjects.items():
            if acoperire_reala[subject] < target_coverage:
                no_conflicts += 1

        # cazul in care un preofesor preda in mai mult de 7 intervale pe saptamana
        for teacher, no_hours in max7_teacher_list.items():
            if no_hours > 7:
                no_conflicts += 1
        return no_conflicts
