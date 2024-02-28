function r = fy(f, x, y)
    % =========================================================================
    % Aproximeaza derivata fata de y a lui f in punctul (x, y).
    % =========================================================================
    if x>1
      r=(f(x+1,y)-f(x-1,y))/2;
    else
      r=0;
    endif
    
endfunction