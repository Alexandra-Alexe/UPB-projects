function out = proximal_2x2_RGB(img, STEP = 0.1)
    % ==============================================================================================
    % Aplica Interpolare Proximala pe imaginea 2 x 2 definita img cu puncte intermediare echidistante.
    % img este o imagine colorata RGB -Red, Green, Blue.
    % =============================================================================================

    x_int = zeros(1,1 + 1/STEP);
    y_int = zeros(1,1 + 1/STEP);
    n = length(x_int);
    out = zeros(n,n,1);
    out = zeros(n,n,2);
    out = zeros(n,n,3);    
    
    % TODO: Extrage canalul rosu al imaginii.
    rosu = img(:,:,1);
    
    % TODO: Extrage canalul verde al imaginii.
    verde = img(:,:,2);
    
    % TODO: Extrage canalul albastru al imaginii.
    albastru = img(:,:,3);
    
    % TODO: Aplic? functia proximal pe cele 3 canale ale imaginii.
    R = zeros(n,n);
    R = proximal_2x2(rosu, STEP );
    
    V = zeros(n,n);
    V = proximal_2x2(verde, STEP );
    
    A = zeros(n,n);
    A = proximal_2x2(albastru, STEP );
    % TODO: Formeaza imaginea finala concaten�nd cele 3 canale de culori.
    out(:,:,1) = R;
    out(:,:,2) = V;
    out(:,:,3) = A;
endfunction
