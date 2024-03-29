#lang racket

(require "etapa2.rkt")

(provide (all-defined-out))

; TODO 1
; După modelul funcției stable-match?, implementați funcția
; get-unstable-couples care primește o listă de logodne
; engagements, o listă de preferințe masculine mpref și o 
; listă de preferințe feminine wpref, și întoarce lista
; tuturor cuplurilor instabile din engagements.
; Precizări (aspecte care se garantează, nu trebuie verificate):
; - fiecare cuplu din lista engagements are pe prima poziție
;   o femeie
; Nu este permisă recursivitatea pe stivă.
; Nu sunt permise alte funcții ajutătoare decât
; better-match-exists? și funcțiile de manipulare a listelor de
; preferințe definite în etapele anterioare.
; Nu este permisă apelarea multiplă a aceleiași funcții pe
; aceleași argumente.
; Folosiți una sau mai multe dintre expresiile let, let*, letrec,
; named let pentru a vă putea conforma acestor restricții.


(define (get-unstable-couples engagements mpref wpref)
  (let ((f (lambda(couple)
              (let* ((firstperson (car couple))
                     (secondperson (cdr couple))
                     (pref-list-first-person (get-pref-list  wpref firstperson))
                     (pref-list-second-person (get-pref-list  mpref secondperson))
                     (rev-engagements (reverse-eng engagements)) 
                     (better-match-for-first-person (better-match-exists?  firstperson secondperson pref-list-first-person mpref rev-engagements))
                     (better-match-for-second-person (better-match-exists? secondperson firstperson pref-list-second-person wpref engagements)))
                (or better-match-for-first-person better-match-for-second-person)))))
    (filter f engagements)))

; TODO 2
; Implementați funcția engage care primește o listă free-men
; de bărbați încă nelogodiți, o listă de logodne parțiale 
; engagements (unde fiecare cuplu are pe prima poziție o femeie),
; o listă de preferințe masculine mpref și o listă de preferințe 
; feminine wpref, și întoarce o listă completă de logodne stabile,
; obținută conform algoritmului Gale-Shapley:
; - cât timp există un bărbat m încă nelogodit
;   - w = prima femeie din preferințele lui m pe care m nu a cerut-o încă
;   - dacă w este nelogodită, adaugă perechea (w, m) la engagements
;   - dacă w este logodită cu m'
;     - dacă w îl preferă pe m lui m'
;       - m' devine liber
;       - actualizează partenerul lui w la m în engagements
;     - altfel, repetă procesul cu următoarea femeie din lista lui m
; Folosiți named let pentru orice proces recursiv ajutător (deci nu
; veți defini funcții ajutătoare recursive).
; Folosiți let și/sau let* pentru a evita calcule duplicate.


(define (engage free-men engagements mpref wpref)
  
      (let loop-for-men ((m free-men) (eng engagements))
        
        (if (null? m)
            eng
            (let* ((M (car m)) (mpref-list (get-pref-list mpref M)))
              
              (let loop-for-women ((w mpref-list))
                (let* ((W (car w)) (M-prim (get-partner eng W)) (wpref-list (get-pref-list wpref W)))
                  (if (not M-prim)
                      (loop-for-men (cdr m) (cons (cons W M) eng))
                      (if (preferable? wpref-list M M-prim)
                         (loop-for-men  (cdr (append m (list M-prim)))  (update-engagements eng W M))
                         (loop-for-women (cdr w))
                         ))))))))

; TODO 3
; Implementați funcția gale-shapley care este un wrapper pentru
; algoritmul implementat de funcția engage. Funcția gale-shapley
; primește doar o listă de preferințe masculine mpref și o listă
; de preferințe feminine wpref și calculează o listă completă de
; logodne stabile conform acestor preferințe.
(define (gale-shapley mpref wpref)
  (engage (get-men mpref) '() mpref wpref))

; TODO 4
; Implementați funcția get-couple-members care primește o listă
; de perechi cu punct și întoarce o listă simplă cu toate elementele 
; care apar în perechi.
; Folosiți funcționale, fără recursivitate explicită.

(define (get-couple-members pair-list)
  (apply append
         (map (lambda (x) (list (car x) (cdr x))) pair-list)))






