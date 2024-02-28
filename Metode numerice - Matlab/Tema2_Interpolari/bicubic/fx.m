function r = fx(f, x, y)
    % =========================================================================
    % Aproximeaza derivata fata de x a lui f in punctul (x, y).
    % =========================================================================
    if y>1
      r=(f(x,y+1)-f(x,y-1))/2;
    else
      r=0;
    endif

endfunction