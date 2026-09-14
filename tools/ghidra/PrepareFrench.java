// Seed only the two observed startup entry points, before auto-analysis.
// @category ForbiddenMemories
import ghidra.app.script.GhidraScript;
import ghidra.program.model.address.Address;
import ghidra.program.model.listing.Function;

public class PrepareFrench extends GhidraScript {
    @Override public void run() throws Exception {
        if (!currentProgram.getLanguageID().toString().equals("MIPS:LE:32:default"))
            throw new IllegalStateException("Expected MIPS little-endian 32-bit language");
        Address entry = toAddr(0x800128ccL);
        if (currentProgram.getMemory().getInt(entry) != 0x3c02800a)
            throw new IllegalStateException("Unexpected French entry point bytes or mapping");
        if (!currentProgram.getMinAddress().equals(toAddr(0x80010000L)))
            throw new IllegalStateException("Unexpected load address");
        currentProgram.getMemory().getBlock(entry).setExecute(true);
        createLabel(entry, "entry_fr", true);
        addEntryPoint(entry);
        disassemble(entry);
        Function f = getFunctionAt(entry);
        if (f == null) createFunction(entry, "entry_fr");
        Address startup = toAddr(0x80012a44L);
        disassemble(startup);
        if (getFunctionAt(startup) == null) createFunction(startup, "startup_candidate_fr");
        // Do not impose a global GP value: startup and potential overlays need
        // separate context validation. Keep unknown functions unnamed.
        println("French startup seeds installed; GP/overlays still require review.");
    }
}
