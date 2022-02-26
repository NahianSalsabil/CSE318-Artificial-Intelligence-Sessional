import org.chocosolver.solver.Model;
import org.chocosolver.solver.Solver;
import org.chocosolver.solver.variables.IntVar;

public class NQueen {

    public static void main(String[] args) {
        Model model = new Model("N Queen");
        int n = 8;
        IntVar[] vars = new IntVar[n];
        for(int i = 0; i < 8; i++){
            vars[i] = model.intVar("Q_"+(i+1), 1, 8);
        }

        for(int i = 0; i < 8; i++){
            for(int j = i+1; j < 8; j++){
                model.arithm(vars[i], "!=", vars[j]).post();
                model.arithm(vars[i], "-", vars[j], "!=", (i-j)).post();
                model.arithm(vars[i], "-", vars[j], "!=", (j-i)).post();
            }
        }

        Solver solver = model.getSolver();
        solver.showStatistics();
        solver.showSolutions();
        solver.findSolution();
    }
}