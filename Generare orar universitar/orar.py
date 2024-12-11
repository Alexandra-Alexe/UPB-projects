from arhiva.utils import pretty_print_timetable
from random import choice
from hc import State
import sys
import mcts
import time

if __name__ == "__main__":
    # extragerea parametrilor si stabilirea tipului de algoritm si de orar ce trebuie rulat
    if len(sys.argv) != 3:
        print("Utilizare: python3.11 orar.py <calea_catre_fisierul_YAML> <algoritm>")
        sys.exit(1)
    
    start_time = time.time()
    input_path = 'arhiva/inputs/' + sys.argv[1]
    algorithm = sys.argv[2]


    if(algorithm == "hc"):

        mystate = State(input_path)
        max_iters = 1000
        iters, states = 0, 0
        state = mystate 

        # in limita nr maxim de iteartii
        while iters < max_iters:
            iters += 1

            best = state 
            best_cost = best.conflicts()
            
            # se parcurg toate starile urmatoare
            for next_state in state.get_next_states():
                states += 1
                no_conf = next_state.conflicts()
                # cand se gaseste un cost mai bun, se retin starea si costul
                if no_conf < best_cost:
                    best = next_state
                    best_cost = no_conf

            if best.conflicts() >= state.conflicts():
                # niciuna dintre starile vecine nu e mai bune (s-a atins un minim local)
                break
            
            state = best
            
        print("Final cost: ", str(best_cost))
        print("Total no states: " + str(states))
        end_time = time.time()
        execution_time = end_time - start_time
        print("Time: ", execution_time, "secunde")
    
    elif algorithm == "mcts":

        N = 'N'
        Q = 'Q'
        STATE = 'state'
        PARENT = 'parent'
        ACTIONS = 'actions'
        budget = 1000
        total_no_states = 0

        state0 = mcts.init_state(input_path)
        tree = mcts.init_node(state0)
        dict_subjects = mcts.generate_dict_subjects(input_path)
        dict_teacher_fav = mcts.generate_dict_teachers_fav(input_path) 
        dict_rooms = mcts.generate_dict_rooms(input_path)

        for x in range(budget):
            # Procesul de selectie porneste din nodul radacina
            node = tree
            state = state0

            # Se coboara in arbore pana la o stare finala sau pana la un nod cu actiuni neexplorate
            while True :
                possibleActions = []
                possibleActions = mcts.get_available_actions(state, dict_teacher_fav, dict_rooms)
                flag = False

                for action in possibleActions:
                    # descoperirea unei actiuni neexplorate
                    if action not in node[ACTIONS].values():
                        flag = True
                        break
                
                # verificarea in cazul unei stari finale
                no_conf = mcts.conflicts(state, dict_subjects, dict_teacher_fav, dict_rooms) 
                if no_conf == 0 or flag is True:
                    break

                # nu exista actiuni de explorat
                selectedAction  = mcts.select_action(node)
                if selectedAction is None:
                    break

                # se "coboara" in arbore prin aplicarea actiunii selectate
                node = node[ACTIONS][selectedAction]
                state = mcts.apply_action(state, selectedAction)
                total_no_states += 1
            
            # cazul actiunilor neexplorate
            if flag is True:
                # se creeaze o lista si se alege random o actiune neexploarata
                actions = mcts.get_available_actions(state, dict_teacher_fav, dict_rooms)
                newActions = []

                for action in actions:
                    if action not in node[ACTIONS].values():
                        newActions.append(action)

                chosenActions = ()
                chosenActions = choice(newActions)

                # se aplica actiunea aleasa, se creeaza un nou nod si se adauga in arbore
                state = mcts.apply_action(state, chosenActions)
                total_no_states += 1
                new_node = mcts.init_node(state, node)
                node[ACTIONS].update({chosenActions: new_node})
                node = new_node

            # se simulează jocul până la ajungerea într-o starea finală (fara conflicte)
            state = node[STATE]
            no_conf = mcts.conflicts(state, dict_subjects, dict_teacher_fav, dict_rooms)
            while no_conf > 0:
                l = mcts.get_available_actions(state, dict_teacher_fav, dict_rooms)
                if len(l) == 0:
                    break
                copy_no_conf = no_conf
                state = mcts.apply_action(state, choice(l))
                total_no_states += 1
                no_conf = mcts.conflicts(state, dict_subjects, dict_teacher_fav, dict_rooms)
                copy_no_conf = no_conf
                if copy_no_conf == no_conf or no_conf > copy_no_conf:
                    break
                
            # se evaluează recompensa in functie de numarul de conflicte din acea stare
            if no_conf == 0:
                reward = 1
            elif no_conf > 0 and no_conf < 5:
                reward = 0.5
            elif no_conf > 5 and no_conf < 10:
                reward = 0.2
            else:
                reward = 0

            # se itereaza pana la radacina si se actualizeaza nr de vizitari si valoarea estimata Q
            while node:
                node[N] += 1
                node[Q] += reward
                node = node[PARENT]

        if tree:
            # se alege actiunea cu cea mai mare valoare estimata
            final_action = mcts.select_action(tree, 0.0)
            total_no_states += 1
            final_state = mcts.apply_action(tree[STATE], final_action)
            print("Final cost: ",mcts.conflicts(final_state, dict_subjects, dict_teacher_fav, dict_rooms))
            print("Total no states: " + str(total_no_states))
            end_time = time.time()
            execution_time = end_time - start_time
            print("Time: ", execution_time, "secunde")
