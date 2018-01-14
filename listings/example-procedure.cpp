class PrintToStdProcedure : public Procedure {
 	public:
 	PrintToStdProcedure(Tag tag, const std::map<int, Data> &data,
     ResultBuffer *resultBuffer) :
 	Procedure(tag, data, resultBuffer) {}

 	void run() override {
 		const auto string = data.at(0);
 		auto basic_string = std::string(string.array,
      static_cast<unsigned long>(string.length));
 		std::cout << basic_string << std::endl;
 		resultBuffer->put(new Result(tag, InputAddress(3, 0),
     Data(new char[1]{1}, 1)));
 	}
 };
