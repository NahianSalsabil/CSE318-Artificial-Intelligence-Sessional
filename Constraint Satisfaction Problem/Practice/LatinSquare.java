/**
 * Copyright (c) 2016, Ecole des Mines de Nantes
 * All rights reserved.
 */

import org.chocosolver.solver.Model;
import org.chocosolver.solver.Solver;
import org.chocosolver.solver.variables.IntVar;

public class LatinSquare {
    public static void main(String[] args) {
        Model model = new Model("Sudoku");

        IntVar[][] bd = model.intVarMatrix("bd", 3, 3, 1, 9);

        IntVar[] r0 = model.intVarArray("r0", 3, 1, 3);
        IntVar[] r1 = model.intVarArray("r1", 3, 1, 3);
        IntVar[] r2 = model.intVarArray("r2", 3, 1, 3);

        IntVar[] c0 = model.intVarArray("c0", 3, 1, 3);
        IntVar[] c1 = model.intVarArray("c1", 3, 1, 3);
        IntVar[] c2 = model.intVarArray("c2", 3, 1, 3);

        model.allDifferent(r0).post();
        model.allDifferent(r1).post();
        model.allDifferent(r2).post();

        model.allDifferent(c0).post();
        model.allDifferent(c1).post();
        model.allDifferent(c2).post();

        for(int j = 0; j < 3; j++){
            model.arithm(bd[0][j], "=", r0[j]).post();
            model.arithm(bd[1][j], "=", r1[j]).post();
            model.arithm(bd[2][j], "=", r2[j]).post();
        }

        for(int i = 0; i < 3; i++){
            model.arithm(bd[i][0], "=", c0[i]).post();
            model.arithm(bd[i][1], "=", c1[i]).post();
            model.arithm(bd[i][2], "=", c2[i]).post();
        }

        Solver solver = model.getSolver();

        solver.showStatistics();
        solver.showSolutions();
        solver.findSolution();

        for ( int i = 0; i < 3; i++) {
            for ( int j = 0; j < 3; j++) {
                System.out.print(" ");
                int k = bd [i][j].getValue();
                System.out.print(k );
            }
            System.out.println();
        }
    }
}