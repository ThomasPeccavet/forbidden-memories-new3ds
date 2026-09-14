// Import a verified SU segment into a fresh full French payload project.
// @category ForbiddenMemories
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import java.nio.file.Files;
import java.nio.file.Paths;

public class PrepareSU extends GhidraScript {
    @Override public void run() throws Exception {
        String[] args = getScriptArgs();
        if (args.length != 1) throw new IllegalArgumentException("Expected SU segment path");
        if (!currentProgram.getLanguageID().toString().equals("MIPS:LE:32:default"))
            throw new IllegalStateException("Expected MIPS little-endian");
        Address base = toAddr(0x80180000L);
        byte[] data = Files.readAllBytes(Paths.get(args[0]));
        if (data.length != 0x8000) throw new IllegalStateException("Unexpected segment size");
        if (!currentProgram.getMinAddress().equals(toAddr(0x80010000L)) ||
            currentProgram.getMemory().getInt(toAddr(0x800128ccL)) != 0x3c02800a)
            throw new IllegalStateException("Expected full French payload");
        currentProgram.getMemory().setBytes(base, data);
        currentProgram.getMemory().getBlock(base).setExecute(true);
        // Known calls from the resident code. Names express locations only.
        long[] seeds = {0x800128ccL, 0x80012a44L,
            0x8018001cL, 0x80180390L, 0x80180e48L,
            0x8002cfdcL, 0x8002d354L, 0x8002d038L, 0x8002d0bcL,
            0x8002d2b4L, 0x8002d4acL, 0x8002d5ccL, 0x8002d544L,
            0x8002d75cL, 0x8002d800L, 0x8002d858L, 0x8002d89cL,
            0x8002d8f4L, 0x8002d988L, 0x8002d990L, 0x8002dbe0L, 0x8002de14L};
        for (long value : seeds) {
            monitor.checkCancelled();
            Address a = toAddr(value);
            addEntryPoint(a);
            disassemble(a);
            if (getFunctionAt(a) == null && createFunction(a, "seed_" + Long.toHexString(value)) == null)
                throw new IllegalStateException("Could not create seed at " + a);
        }
        println("SU segment mapped and startup/state seeds created.");
        println("Synthetic static snapshot: other overlays remain absent; GP/prototypes require review.");
    }
}
