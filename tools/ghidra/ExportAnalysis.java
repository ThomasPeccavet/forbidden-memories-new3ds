// Export recognized functions, pseudo-C, and resolved calls after auto-analysis.
// @category ForbiddenMemories
import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.program.model.listing.Instruction;
import ghidra.program.model.listing.InstructionIterator;
import ghidra.program.model.symbol.Reference;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.charset.StandardCharsets;
import java.io.BufferedWriter;

public class ExportAnalysis extends GhidraScript {
    private String cell(String s) {
        return s == null ? "" : s.replace('\t', ' ').replace('\r', ' ').replace('\n', ' ');
    }
    @Override public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) throw new IllegalArgumentException("Expected fresh output directory");
        Path out = Paths.get(args[0]);
        Files.createDirectories(out);
        Path c = out.resolve("pseudo-c");
        // Reject reuse rather than mixing results from different runs.
        Files.createDirectory(c);
        DecompInterface dec = new DecompInterface();
        int total = 0, failed = 0;
        try {
            if (!dec.openProgram(currentProgram)) throw new IllegalStateException(dec.getLastMessage());
            try (BufferedWriter functions = Files.newBufferedWriter(out.resolve("functions.tsv"), StandardCharsets.UTF_8);
                 BufferedWriter calls = Files.newBufferedWriter(out.resolve("calls.tsv"), StandardCharsets.UTF_8)) {
                functions.write("address\tname\tbody_bytes\tstatus\tmessage\n");
                calls.write("caller\tsite\ttarget\n");
                FunctionIterator it = currentProgram.getFunctionManager().getFunctions(true);
                while (it.hasNext()) {
                    monitor.checkCancelled();
                    Function f = it.next();
                    if (f.isExternal()) continue;
                    total++;
                    DecompileResults r = dec.decompileFunction(f, 60, monitor);
                    boolean ok = r.decompileCompleted() && r.getDecompiledFunction() != null;
                    if (ok) {
                        Files.write(c.resolve(f.getEntryPoint().toString() + ".c"),
                            ("/* Analysis pseudo-C, not buildable source. */\n" + r.getDecompiledFunction().getC()).getBytes(StandardCharsets.UTF_8));
                    } else failed++;
                    functions.write(f.getEntryPoint() + "\t" + cell(f.getName()) + "\t" + f.getBody().getNumAddresses()
                        + "\t" + (ok ? "ok" : "failed") + "\t" + cell(r.getErrorMessage()) + "\n");
                    InstructionIterator instructions = currentProgram.getListing().getInstructions(f.getBody(), true);
                    while (instructions.hasNext()) {
                        Instruction ins = instructions.next();
                        if (!ins.getFlowType().isCall()) continue;
                        boolean found = false;
                        for (Reference ref : ins.getReferencesFrom()) {
                            if (!ref.getReferenceType().isCall()) continue;
                            calls.write(f.getEntryPoint() + "\t" + ins.getAddress() + "\t" + ref.getToAddress() + "\n");
                            found = true;
                        }
                        if (!found) calls.write(f.getEntryPoint() + "\t" + ins.getAddress() + "\tunresolved\n");
                    }
                }
            }
            if (total == 0) throw new IllegalStateException("No functions recognized");
            Files.write(out.resolve("COMPLETE.txt"), ("functions=" + total + "\nfailed=" + failed
                + "\nOnly recognized functions; overlays and indirect calls may be missing.\n").getBytes(StandardCharsets.UTF_8));
        } finally { dec.dispose(); }
    }
}
