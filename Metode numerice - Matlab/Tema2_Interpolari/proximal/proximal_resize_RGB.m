function out = proximal_resize_RGB(img, p, q)
    % =========================================================================
    % Redimensioneaza imaginea img astfel �nc�t aceasta save fie de dimensiune p x q.
    % Imaginea img este colorata.
    % =========================================================================

    % TODO: Extrage canalul rosu al imaginii.
    
    R=img(:,:,1);
    % TODO: Extrage canalul verde al imaginii.
    V=img(:,:,2);
    % TODO: Extrage canalul albastru al imaginii.
    A=img(:,:,3);
    % TODO: Aplica functia proximal pe cele 3 canale ale imaginii.
    R=proximal_resize(R);
    V=proximal_resize(V);
    A=proximal_resize(A);
    % TODO: Formeaza imaginea finala concaten�nd cele 3 canale de culori.
    out(:,:,1)=R;
    out(:,:,2)=V;
    out(:,:,3)=A;
endfunction
