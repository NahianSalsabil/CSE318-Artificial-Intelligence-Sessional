/**
 * Copyright (c) 2016, Ecole des Mines de Nantes
 * All rights reserved.
 */

import org.chocosolver.solver.Model;
import org.chocosolver.solver.Solver;
import org.chocosolver.solver.variables.IntVar;

public class Sudoku {
    public static void main(String[] args) {
        Model model = new Model("Sudoku");

        IntVar[][] bd = model.intVarMatrix("bd", 9, 9, 1, 9);

        IntVar[] r0 = model.intVarArray("r0", 9, 1, 9);
        IntVar[] r1 = model.intVarArray("r1", 9, 1, 9);
        IntVar[] r2 = model.intVarArray("r2", 9, 1, 9);
        IntVar[] r3 = model.intVarArray("r3", 9, 1, 9);
        IntVar[] r4 = model.intVarArray("r4", 9, 1, 9);
        IntVar[] r5 = model.intVarArray("r5", 9, 1, 9);
        IntVar[] r6 = model.intVarArray("r6", 9, 1, 9);
        IntVar[] r7 = model.intVarArray("r7", 9, 1, 9);
        IntVar[] r8 = model.intVarArray("r8", 9, 1, 9);

        IntVar[] c0 = model.intVarArray("c0", 9, 1, 9);
        IntVar[] c1 = model.intVarArray("c1", 9, 1, 9);
        IntVar[] c2 = model.intVarArray("c2", 9, 1, 9);
        IntVar[] c3 = model.intVarArray("c3", 9, 1, 9);
        IntVar[] c4 = model.intVarArray("c4", 9, 1, 9);
        IntVar[] c5 = model.intVarArray("c5", 9, 1, 9);
        IntVar[] c6 = model.intVarArray("c6", 9, 1, 9);
        IntVar[] c7 = model.intVarArray("c7", 9, 1, 9);
        IntVar[] c8 = model.intVarArray("c8", 9, 1, 9);

        IntVar[] b0 = model.intVarArray("b0", 9, 1, 9);
        IntVar[] b1 = model.intVarArray("b1", 9, 1, 9);
        IntVar[] b2 = model.intVarArray("b2", 9, 1, 9);
        IntVar[] b3 = model.intVarArray("b3", 9, 1, 9);
        IntVar[] b4 = model.intVarArray("b4", 9, 1, 9);
        IntVar[] b5 = model.intVarArray("b5", 9, 1, 9);
        IntVar[] b6 = model.intVarArray("b6", 9, 1, 9);
        IntVar[] b7 = model.intVarArray("b7", 9, 1, 9);
        IntVar[] b8 = model.intVarArray("b8", 9, 1, 9);

        //x-sudoku
        IntVar[] x0 = model.intVarArray("x0", 9, 1, 9);
        IntVar[] x1 = model.intVarArray("x1", 9, 1, 9);

        model.allDifferent(r0).post();
        model.allDifferent(r1).post();
        model.allDifferent(r2).post();
        model.allDifferent(r3).post();
        model.allDifferent(r4).post();
        model.allDifferent(r5).post();
        model.allDifferent(r6).post();
        model.allDifferent(r7).post();
        model.allDifferent(r8).post();

        model.allDifferent(c0).post();
        model.allDifferent(c1).post();
        model.allDifferent(c2).post();
        model.allDifferent(c3).post();
        model.allDifferent(c4).post();
        model.allDifferent(c5).post();
        model.allDifferent(c6).post();
        model.allDifferent(c7).post();
        model.allDifferent(c8).post();

        model.allDifferent(b0).post();
        model.allDifferent(b1).post();
        model.allDifferent(b2).post();
        model.allDifferent(b3).post();
        model.allDifferent(b4).post();
        model.allDifferent(b5).post();
        model.allDifferent(b6).post();
        model.allDifferent(b7).post();
        model.allDifferent(b8).post();

        //x-sudoku
        model.allDifferent(x0).post();
        model.allDifferent(x1).post();

        model.arithm (bd[0][0], "=", 4).post();
        model.arithm (bd[0][3], "=", 8).post();
        model.arithm (bd[0][4], "=", 3).post();
        model.arithm (bd[0][5], "=", 5).post();
        model.arithm (bd[0][6], "=", 2).post();
        model.arithm (bd[0][8], "=", 1).post();

        model.arithm(bd[1][1], "=", 1).post();

        model.arithm (bd[2][1], "=", 8).post();
        model.arithm (bd[2][2], "=", 3).post();
        model.arithm (bd[2][4], "=", 7).post();

        model.arithm (bd[3][3], "=", 2).post();
        model.arithm (bd[3][4], "=", 1).post();
        model.arithm (bd[3][5], "=", 8).post();
        model.arithm (bd[3][6], "=", 9).post();
        model.arithm (bd[3][7], "=", 5).post();
        model.arithm (bd[3][8], "=", 7).post();

        model.arithm (bd[4][3], "=", 7).post();
        model.arithm (bd[4][4], "=", 5).post();
        model.arithm (bd[4][5], "=", 6).post();
        model.arithm (bd[4][6], "=", 1).post();
        model.arithm (bd[4][7], "=", 3).post();
        model.arithm (bd[4][8], "=", 4).post();

        model.arithm (bd[5][0], "=", 1).post();
        model.arithm (bd[5][1], "=", 7).post();
        model.arithm (bd[5][2], "=", 5).post();
        model.arithm (bd[5][3], "=", 3).post();
        model.arithm (bd[5][4], "=", 4).post();
        model.arithm (bd[5][5], "=", 9).post();

        model.arithm (bd[6][7], "=", 1).post();

        model.arithm (bd[8][2], "=", 1).post();
        model.arithm (bd[8][5], "=", 7).post();
        model.arithm (bd[8][8], "=", 6).post();

        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                model.arithm(bd[i][j], "=", b0[i*3+j]).post();
                model.arithm(bd[i][j+3], "=", b1[i*3+j]).post();
                model.arithm(bd[i][j+6], "=", b2[i*3+j]).post();
                model.arithm(bd[i+3][j], "=", b3[i*3+j]).post();
                model.arithm(bd[i+3][j+3], "=", b4[i*3+j]).post();
                model.arithm(bd[i+3][j+6], "=", b5[i*3+j]).post();
                model.arithm(bd[i+6][j], "=", b6[i*3+j]).post();
                model.arithm(bd[i+6][j+3], "=", b7[i*3+j]).post();
                model.arithm(bd[i+6][j+6], "=", b8[i*3+j]).post();
            }
        }

        for(int j = 0; j < 9; j++){
            model.arithm(bd[0][j], "=", r0[j]).post();
            model.arithm(bd[1][j], "=", r1[j]).post();
            model.arithm(bd[2][j], "=", r2[j]).post();
            model.arithm(bd[3][j], "=", r3[j]).post();
            model.arithm(bd[4][j], "=", r4[j]).post();
            model.arithm(bd[5][j], "=", r5[j]).post();
            model.arithm(bd[6][j], "=", r6[j]).post();
            model.arithm(bd[7][j], "=", r7[j]).post();
            model.arithm(bd[8][j], "=", r8[j]).post();
        }

        for(int i = 0; i < 9; i++){
            model.arithm(bd[i][0], "=", c0[i]).post();
            model.arithm(bd[i][1], "=", c1[i]).post();
            model.arithm(bd[i][2], "=", c2[i]).post();
            model.arithm(bd[i][3], "=", c3[i]).post();
            model.arithm(bd[i][4], "=", c4[i]).post();
            model.arithm(bd[i][5], "=", c5[i]).post();
            model.arithm(bd[i][6], "=", c6[i]).post();
            model.arithm(bd[i][7], "=", c7[i]).post();
            model.arithm(bd[i][8], "=", c8[i]).post();
        }

        //x-sudoku
        for(int i = 0; i < 9; i++){
            model.arithm(bd[i][i], "=", x0[i]).post();
            model.arithm(bd[i][8-i], "=", x1[i]).post();
        }

        Solver solver = model.getSolver();

        solver.showStatistics();
        solver.showSolutions();
        solver.findSolution();

        for ( int i = 0; i < 9; i++) {
            for ( int j = 0; j < 9; j++) {
                System.out.print(" ");
                int k = bd [i][j].getValue();
                System.out.print(k );
            }
            System.out.println();
        }
    }
}