function R = proximal_rotate(I, rotation_angle)
    % =========================================================================
    % Roteste imaginea alb-negru I de dimensiune m x n cu unghiul rotation_angle,
    % aplic�nd Interpolare Proximala.
    % rotation_angle este exprimat �n radiani.
    % =========================================================================
    [m n nr_colors] = size(I);
    
    % Se converteste imaginea de intrare la alb-negru, daca este cazul.
    if nr_colors > 1
        R = -1;
        return
    endif

    % Obs:
    % Atunci c�nd se aplica o scalare, punctul (0, 0) al imaginii nu se va deplasa.
    % �n Octave, pixelii imaginilor sunt indexati de la 1 la n.
    % Daca se lucreaza �n indici de la 1 la n si se inmultesc x si y cu s_x respectiv s_y,
    % atunci originea imaginii se va deplasa de la (1, 1) la (sx, sy)!
    % De aceea, trebuie lucrat cu indici �n intervalul [0, n - 1].

    % TODO: Calculeaza cosinus si sinus de rotation_angle.
    c = cos(rotation_angle);
    s = sin(rotation_angle);
    
    % TODO: Initializeaza matricea finala.
    I = double(I);
    R = zeros(m,n);
    % TODO: Calculeaza matricea de transformare.
    T(1,1) = c;
    T(1,2) = s;
    T(2,1) = -s;
    T(2,2) = c;
    % TODO: Inverseaza matricea de transformare, FOLOSIND doar functii predefinite!
    % Se parcurge fiecare pixel din imagine.
    for y = 0 : m - 1
        for x = 0 : n - 1
            % TODO: Aplica transformarea inversa asupra (x, y) si calculeaza x_p si y_p
            % din spatiul imaginii initiale.
            P = T*[x; y];
            y_p = P(2);
            x_p = P(1);
            % TODO: Trece (xp, yp) din sistemul de coordonate [0, n - 1] �n
            % sistemul de coordonate [1, n] pentru a aplica interpolarea.
            x_p = x_p + 1;
            y_p = y_p + 1;
            
            % TODO: Daca xp sau yp se afla �n exteriorul imaginii,
            % se pune un pixel negru si se trece mai departe.
            if( x_p < 1 || x_p > n || y_p < 1 || y_p > n)
                continue;
            endif
            
            % TODO: Afla punctele ce �nconjoara(xp, yp).
            x1 = floor(x_p);
            x2 = floor(x_p)  + 1;
            y1 = floor(y_p);
            y2 = floor(y_p) + 1;
            % TODO: Calculeaza coeficientii de interpolare notati cu a
            % Obs: Se poate folosi o functie auxiliara �n care sau se calculeze coeficientii,
            % conform formulei.
            N = [ 1 x1 y1 x1*y1; 1 x1 y2 x1*y2; 1 x2 y1 y1*x2; 1 x2 y2 x2*y2 ];
            N = inv(N);
            X = zeros(4,1);
            X(1,1) = I(y1,x1);
            X(2,1) = I(y2,x1);
            X(3,1) = I(y1,x2);
            X(4,1) = I(y2,x2);
            A = zeros(4,1);
            A = N*X;
            a0 = A(1,1);
            a1 = A(2,1);
            a2 = A(3,1);
            a3 = A(4,1);
            % TODO: Calculeaza valoarea interpolata a pixelului (x, y).
              R(y + 1, x + 1) = a0 + a1*x_p + a2*y_p + a3*x_p*y_p; 
        endfor
    endfor

    % TODO: Transforma matricea rezultata �n uint8 pentru a fi o imagine valida.
    R = uint8(R);
endfunction
