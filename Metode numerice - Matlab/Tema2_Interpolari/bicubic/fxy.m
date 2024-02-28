function r = fxy(f, x, y)
    % =========================================================================
    % Aproximeaza derivata fata de x si y a lui f in punctul (x, y).
    % =========================================================================
    if x>1 && y>1
      r=(f(x-1,y-1)+f(x+1,y+1)-f(x+1,y-1)-f(x-1,y+1))/4;
    else
      r=0;
    endif
    
endfunction