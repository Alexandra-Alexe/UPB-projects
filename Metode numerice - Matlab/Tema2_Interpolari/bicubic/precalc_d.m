function [Ix, Iy, Ixy] = precalc_d(I)
    % =========================================================================
    % Prealculeaza matricile Ix, Iy si Ixy ce contin derivatele dx, dy, dxy ale 
    % imaginii I pentru fiecare pixel al acesteia.
    % =========================================================================
    
    % Obtinem dimensiunea imaginii.
    [m n nr_colors] = size(I);
    
    % TODO: Tranforma matricea I in double.
    I=double(I);
    Ix=zeros(m,n,nr_colors);
    Iy=zeros(m,n,nr_colors);
    Ixy=zeros(m,n,nr_colors);
    % TODO: Calculeaza matricea cu derivate fata de x Ix.
    for k=1:nr_colors
      for x=1:m
        for y=1:n-1
          Ix(x,y,k)=fx(I(:,:,k),x,y);
        endfor
      endfor
      for x=1:m-1
        for y=1:n
          Iy(x,y,k)=fy(I(:,:,k),x,y);
        endfor
      endfor
      for x=1:m-1
        for y=1:n-1
          Ixy(x,y,k)=fxy(I(:,:,k),x,y);
        endfor
      endfor
    endfor
      

    % TODO: Calculeaza matricea cu derivate fata de y Iy.
    for k=1:nr_colors
      for x=1:m-1
        for y=1:n
          Iy(x,y,k)=fy(I(:,:,k),x,y);
        endfor
      endfor
      for x=1:m
        for y=1:n-1
          Ix(x,y,k)=fx(I(:,:,k),x,y);
        endfor
      endfor
      for x=1:m-1
        for y=1:n-1
          Ixy(x,y,k)=fxy(I(:,:,k),x,y);
        endfor
      endfor
    endfor

endfunction
