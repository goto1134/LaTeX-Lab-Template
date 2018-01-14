int main(int argc, char **argv) {

    int provided_thread_level;
    MPIGraphSchemeInit(&argc, &argv, &provided_thread_level);

    auto map = ModuleMapBuilder()
            .add(MPIGraphSchemeModule(ModuleData(1, 1, INITIAL),
             Procedure::constructor<PrintToStdProcedure>()))
            .add(MPIGraphSchemeModule(ModuleData(2, 1, FINAL),
             Procedure::constructor<GoodByeProcedure>()))
            .add(MPIGraphSchemeModule(ModuleData(3, 1),
             Procedure::constructor<MiddleProcedure>())).build();


    MPIGraphSchemeStart(&map);

    MPIGraphSchemeFinalize();
    return 0;
}
