function A = bicubic_coef(f, Ix, Iy, Ixy, x1, y1, x2, y2)
    % =========================================================================
    % Calculeaz? coeficien?ii de Interpolare Bicubic? pentru 4 puncte al?turate
    % =========================================================================

    % TODO: Calculeaz? matricile intermediare.
    M=[1 0 0 0; 0 0 1 0; -3 3 -2 -1; 2 -2 1 1];
    F=zeros(4,4);
    F(1,1)=f(y1,x1);
    F(1,2)=f(y2,x1);
    F(2,1)=f(y1,x2);
    F(2,2)=f(y2,x2);
    F(1,3)=Iy(y1,x1);
    F(1,4)=Iy(y2,x1);
    F(2,3)=Iy(y1,x2);
    F(2,4)=Iy(y2,x2);
    F(3,1)=Ix(y1,x1);
    F(3,2)=Ix(y2,x1);
    F(4,1)=Ix(y1,x2);
    F(4,2)=Ix(y2,x2);
    F(3,3)=Ixy(y1,x1);
    F(3,4)=Ixy(y2,x1);
    F(4,3)=Ixy(y1,x2);
    F(4,4)=Ixy(y2,x2);
    % TODO: Converte?te matricile intermediare la double.
    M=double(M);
    F=double(F);
    % TODO: Calculeaz? matricea final?.
    A = M*F*M';
endfunction