function out = proximal_rotate_RGB(img, rotation_angle)
    % =========================================================================
    % Aplica Interpolarea Proximala pentru a roti o imagine RGB cu un unghi dat.
    % =========================================================================
    
    % TODO: Extrage canalul rosu al imaginii.
    R = img(:,:,1);
    % TODO: Extrage canalul verde al imaginii.
    V = img(:,:,2);
    % TODO: Extrage canalul albastru al imaginii.
    A = img(:,:,3);
    % TODO: Aplica rotatia pe fiecare canal al imaginii.
    R = proximal_rotate(R, rotation_angle);
    V = proximal_rotate(V, rotation_angle);
    A = proximal_rotate(A, rotation_angle);
    % TODO: Formeaza imaginea finala concaten�nd cele 3 canale de culori.
    out(:,:,1) = R;
    out(:,:,2) = V;
    out(:,:,3) = A;
endfunction