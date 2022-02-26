import org.chocosolver.solver.Model;
import org.chocosolver.solver.Solver;
import org.chocosolver.solver.variables.IntVar;

public class OnePlusTwo {

    public static void main(String[] args) {
        Model model = new Model("TWO+TWO=FOUR");
        IntVar T = model.intVar("T", 1, 9, false);
        IntVar W = model.intVar("W", 0, 9, false);
        IntVar O = model.intVar("O", 0, 9, false);
        IntVar M = model.intVar("M", 1, 9, false);
        IntVar N = model.intVar("N", 0, 9, false);
        IntVar P = model.intVar("P", 0, 9, false);
        IntVar F = model.intVar("F", 1, 9, false);
        IntVar U = model.intVar("U", 0, 9, false);
        IntVar R = model.intVar("R", 0, 9, false);

        model.allDifferent(new IntVar[]{T, W, O, M, N, P, F, U, R}).post();

        IntVar[] ALL = new IntVar[]{
                T, W, O,
                M, N, P,
                F, O, U, R};
        int[] COEFFS = new int[]{
                100, 10, 1,
                100, 10, 1,
                -1000, -100, -10, -1};
        model.scalar(ALL, COEFFS, "=", 0).post();

        Solver solver = model.getSolver();
        solver.showStatistics();
        solver.showSolutions();
        solver.findSolution();

        System.out.println("  " + T + " " + W + " " + O);
        System.out.println("  " + T + " " + W + " " + O);
        System.out.println(F + " " + O + " " + U + " " + R);
    }
}