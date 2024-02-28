function [R1 R2] = PageRank( nume, d, eps)
	% Calculeaza indicii PageRank pentru cele 3 cerinte
	% Scrie fisierul de iesire nume.out
    fi = fopen(nume, "r");
    N = fgetl(fi);
    N = str2num(N);
    R1 = Iterative(nume, d, eps);
    fclose(fi);
    nume = [nume ".out"];
    fprintf(fo,"%d\n",N);
    fprintf(fo,"\n");
    fo = fopen(nume, "w");
    fprintf(fo,"%f \n", R1);
    fclose(fo);
endfunction
