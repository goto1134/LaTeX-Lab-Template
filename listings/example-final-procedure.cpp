class GoodByeProcedure : public Procedure {
public:
    GoodByeProcedure(Tag tag, const std::map<int, Data> &data,
      ResultBuffer *resultBuffer) : Procedure(tag, data, resultBuffer) {}

    void run() override {
        std::cout << "Program finished\n";
        resultBuffer->finish(tag);
    }
};
