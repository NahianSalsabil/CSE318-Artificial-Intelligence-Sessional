/**
 * Copyright (c) 2016, Ecole des Mines de Nantes
 * All rights reserved.
 */

import org.chocosolver.solver.Model;
import org.chocosolver.solver.Solver;
import org.chocosolver.solver.variables.IntVar;

public class Magic_Square {
    public static void main(String[] args) {
        Model model = new Model("X Sum");

        IntVar[] bd = model.intVarArray("bd", 9, 1, 9);

        IntVar[] r0 = model.intVarArray("r0", 3, 1, 9);
        IntVar[] r1 = model.intVarArray("r1", 3, 1, 9);
        IntVar[] r2 = model.intVarArray("r2", 3, 1, 9);

        IntVar[] c0 = model.intVarArray("c0", 3, 1, 9);
        IntVar[] c1 = model.intVarArray("c1", 3, 1, 9);
        IntVar[] c2 = model.intVarArray("c2", 3, 1, 9);

        IntVar[] d0 = model.intVarArray("d0", 3, 1, 9);
        IntVar[] d1 = model.intVarArray("d1", 3, 1, 9);

        IntVar[] rows0 = new IntVar[]{
                r0[0], r0[1], r0[2]
        };
        IntVar[] rows1 = new IntVar[]{
                r1[0], r1[1], r1[2]
        };
        IntVar[] rows2 = new IntVar[]{
                r2[0], r2[1], r2[2]
        };

        IntVar[] col0 = new IntVar[]{
                c0[0], c0[1], c0[2]
        };
        IntVar[] col1 = new IntVar[]{
                c1[0], c1[1], c1[2]
        };
        IntVar[] col2 = new IntVar[]{
                c2[0], c2[1], c2[2]
        };

        IntVar[] dia0 = new IntVar[]{
                d0[0], d0[1], d0[2]
        };
        IntVar[] dia1 = new IntVar[]{
                d1[0], d1[1], d1[2]
        };

        int[] weight = new int[]{
            1,1,1
        };
        model.scalar(rows0, weight, "=", 15).post();
        model.scalar(rows1, weight, "=", 15).post();
        model.scalar(rows2, weight, "=", 15).post();

        model.scalar(col0, weight, "=", 15).post();
        model.scalar(col1, weight, "=", 15).post();
        model.scalar(col2, weight, "=", 15).post();

        model.scalar(dia0, weight, "=", 15).post();
        model.scalar(dia1, weight, "=", 15).post();

        //row
        for(int i = 0; i < 3; i++){
                model.arithm(bd[i+0], "=", r0[i]).post();
                model.arithm(bd[i+3], "=", r1[i]).post();
                model.arithm(bd[i+6], "=", r2[i]).post();
        }
        //column
        for(int i = 0; i < 3; i++){
            model.arithm(bd[i*3], "=", c0[i]).post();
            model.arithm(bd[i*3+1], "=", c1[i]).post();
            model.arithm(bd[i*3+2], "=", c2[i]).post();
        }
        //diagonal
        for(int i = 0; i < 3; i++){
            model.arithm(bd[i*3+i], "=", d0[i]).post();
            model.arithm(bd[i*3+2-i], "=", d1[i]).post();
        }

        model.allDifferent(bd).post();
        Solver solver = model.getSolver();
        solver.showStatistics();
        solver.showSolutions();
        solver.findSolution();

        for ( int i = 0; i < 9; i++) {
            System.out.print(" ");
            int k = bd [i].getValue();
            System.out.print(k );
            System.out.println();
        }
    }
}