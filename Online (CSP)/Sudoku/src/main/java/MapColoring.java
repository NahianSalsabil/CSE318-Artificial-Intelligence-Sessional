import org.chocosolver.solver.Model;
import org.chocosolver.solver.Solver;
import org.chocosolver.solver.variables.IntVar;

public class MapColoring {

    public static void main(String[] args) {
        Model model = new Model("Map Coloring");
        int R = 1;
        int G = 2;
        int B = 3;

        IntVar WA = model.intVar("WA", new int[]{R,G,B});
        IntVar NT = model.intVar("NT", new int[]{R,G,B});
        IntVar Q = model.intVar("Q", new int[]{R,G,B});
        IntVar NSW = model.intVar("NSW", new int[]{R,G,B});
        IntVar V = model.intVar("V", new int[]{R,G,B});
        IntVar SA = model.intVar("SA", new int[]{R,G,B});
        IntVar T = model.intVar("T", new int[]{R,G,B});

        model.arithm(WA, "!=", NT).post();
        model.arithm(WA, "!=", SA).post();
        model.arithm(NT, "!=", SA).post();
        model.arithm(NT, "!=", Q).post();
        model.arithm(Q, "!=", SA).post();
        model.arithm(Q, "!=", NSW).post();
        model.arithm(NSW, "!=", V).post();
        model.arithm(NSW, "!=", SA).post();
        model.arithm(V, "!=", SA).post();

        Solver solver = model.getSolver();
        solver.showStatistics();
        solver.showSolutions();
        solver.findSolution();
    }
}