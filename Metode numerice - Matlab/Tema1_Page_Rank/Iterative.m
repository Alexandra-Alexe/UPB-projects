function PR = Iterative(nume, d, eps)
	% Functia care calculeaza matricea R folosind algoritmul iterativ.
	% Intrari:
	%	-> nume: numele fisierului din care se citeste;
	%	-> d: coeficentul d, adica probabilitatea ca un anumit navigator sa continue navigarea (0.85 in cele mai multe cazuri)
	%	-> eps: eruarea care apare in algoritm.
	% Iesiri:
	%	-> R: vectorul de PageRank-uri acordat pentru fiecare pagina.
  
  %deschid fisierul
  fid = fopen(nume, "r"); 
  %citesc numarul de site-uri si fac initializari
  N = fgetl(fid);
  L = zeros( 1, str2num(N) );
  A = zeros(str2num(N),str2num(N));
  M = zeros(str2num(N),str2num(N));
  one = ones( str2num(N), 1);
  v_curr = ones( str2num(N), 1);
  v_curr = v_curr*1/str2num(N);
  
  %construiesc matricea A si vectorul L
  for i = 1:str2num(N) 
    %in variabila aux citesc cate o linie din fisier
    aux = fgetl(fid);  
    aux = str2num(aux);
    k = 3;
    for j = 1:aux(2)
      A(aux(1),aux(k)) = 1;
      k = k + 1;
     endfor
     L(i) =  aux(2);
  endfor
  
  %cazul site-urilor care se apeleaza pe ele insele 
  for i =1:str2num(N)
	  if A(i,i) == 1
      L(i) = L(i)-1;
	  	A(i,i) = 0;
	  endif
  endfor
  
  %construirea matricei M
  for i = 1:str2num(N) 
    for j = 1:str2num(N)
      if( A(j,i) == 1)
        M(i,j) = 1 / L(j);
       endif
    endfor
  endfor
  
  %aplic formula data in cerinta
  while(1)
    % valorea precedent devine valoarea curenta
    v_prev = v_curr; 
    % valoarea curenta este calculata conform formulei
    v_curr = d*M*v_curr + (1-d/str2num(N))*one;
    % conditia de oprire este data de valoarea erorii dintre cele 2 valori
    if( abs(v_curr - v_prev) <eps)
      break;
    endif
  endwhile
  
  %indicii page rank vor lua ultima valoare precedenta
  PR = v_prev; 
  %inchid fisierul 
  fclose(fid);
  endfunction