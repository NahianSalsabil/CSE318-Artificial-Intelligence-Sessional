/**
 * Copyright (c) 2016, Ecole des Mines de Nantes
 * All rights reserved.
 */

import org.chocosolver.solver.Model;
import org.chocosolver.solver.Solver;
import org.chocosolver.solver.variables.IntVar;

public class KillerSudoku {
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


        IntVar[] cage1 = new IntVar[]{
                c0[0], c0[1]
        };

        IntVar[] cage2 = new IntVar[]{
                r0[1], r0[2],r0[3], r0[4], r1[4]
        };

        IntVar[] cage3 = new IntVar[]{
                c5[0], c5[1]
        };

        IntVar[] cage4 = new IntVar[]{
                c6[0], c6[1], c7[1], c7[2]
        };

        IntVar[] cage29 = new IntVar[]{
                c8[0], c8[1], c8[2], c7[0]
        };

        IntVar[] cage5 = new IntVar[]{
                c1[1], c1[2]
        };

        IntVar[] cage6 = new IntVar[]{
                c2[1], c2[2]
        };

        IntVar[] cage7 = new IntVar[]{
                c3[1], c3[2], c3[3]
        };

        IntVar[] cage8 = new IntVar[]{
                c4[2], c4[3]
        };

        IntVar[] cage9 = new IntVar[]{
                c0[2], c0[3]
        };

        IntVar[] cage10 = new IntVar[]{
                r2[5], r2[6]
        };

        IntVar[] cage11 = new IntVar[]{
                c1[3], c1[5], c2[3],c2[4], c2[5], c3[4]
        };

        IntVar[] cage12 = new IntVar[]{
                r3[5], r3[6]
        };

        IntVar[] cage13 = new IntVar[]{
                r3[7], r3[8]
        };

        IntVar[] cage14 = new IntVar[]{
                r4[0], r4[1]
        };

        IntVar[] cage15 = new IntVar[]{
                r4[4], r4[5], r4[6], r4[7],  r4[8]
        };
        IntVar[] cage16 = new IntVar[]{
                c0[5], c0[6]
        };

        IntVar[] cage17 = new IntVar[]{
                c3[5], c3[6], c3[7]
        };

        IntVar[] cage18 = new IntVar[]{
                c4[5], c4[6]
        };

        IntVar[] cage19 = new IntVar[]{
                r5[5], r5[6]
        };

        IntVar[] cage20 = new IntVar[]{
                r5[7], r5[8]
        };

        IntVar[] cage21 = new IntVar[]{
                c1[6], c1[7]
        };

        IntVar[] cage22 = new IntVar[]{
                c2[6], c2[7]
        };

        IntVar[] cage23 = new IntVar[]{
                r6[5], r6[6]
        };

        IntVar[] cage24 = new IntVar[]{
                c6[7], c6[8], c7[6],c7[7]
        };

        IntVar[] cage25 = new IntVar[]{
                c7[8], c8[6],c8[7],c8[8]
        };
        IntVar[] cage26 = new IntVar[]{
                c0[7], c0[8]
        };

        IntVar[] cage27 = new IntVar[]{
                r8[1], r8[2], r8[3], r8[4], r7[4]
        };

        IntVar[] cage28 = new IntVar[]{
                c5[7], c5[8]
        };



        int[] weight2 = new int[]{
                1,1
        };

        int[] weight3 = new int[]{
                1,1,1
        };
        int[] weight4 = new int[]{
                1,1,1,1
        };
        int[] weight5 = new int[]{
                1,1,1,1,1
        };
        int[] weight6 = new int[]{
                1,1,1,1,1,1
        };

        model.scalar(cage1, weight2, "=", 13).post();
        model.scalar(cage2, weight5, "=", 21).post();
        model.scalar(cage3, weight2, "=", 12).post();
        model.scalar(cage4, weight4, "=", 24).post();
        model.scalar(cage29, weight4, "=", 17).post();

        model.scalar(cage5, weight2, "=", 9).post();
        model.scalar(cage6, weight2, "=", 11).post();
        model.scalar(cage7, weight3, "=", 13).post();

        model.scalar(cage8, weight2, "=", 11).post();
        model.scalar(cage9, weight2, "=", 5).post();
        model.scalar(cage10, weight2, "=", 11).post();

        model.scalar(cage11, weight6, "=", 33).post();
        model.scalar(cage12, weight2, "=", 15).post();
        model.scalar(cage13, weight2, "=", 9).post();

        model.scalar(cage14, weight2, "=", 8).post();
        model.scalar(cage15, weight5, "=", 20).post();

        model.scalar(cage16, weight2, "=", 17).post();
        model.scalar(cage17, weight3, "=", 13).post();
        model.scalar(cage18, weight2, "=", 10).post();
        model.scalar(cage19, weight2, "=", 9).post();
        model.scalar(cage20, weight2, "=", 8).post();

        model.scalar(cage21, weight2, "=", 13).post();
        model.scalar(cage22, weight2, "=", 5).post();
        model.scalar(cage23, weight2, "=", 10).post();
        model.scalar(cage24, weight4, "=", 18).post();
        model.scalar(cage25, weight4, "=", 25).post();

        model.scalar(cage26, weight2, "=", 5).post();
        model.scalar(cage27, weight5, "=", 31).post();
        model.scalar(cage28, weight2, "=", 9).post();




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