STEP1_SRC = page.cpp page.hpp option.hpp option.cpp utility.hpp utility.cpp
SRC = $(STEP1_SRC) story.cpp story.hpp graph.hpp graph.cpp
TARGET = cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4
all: $(TARGET)
cyoa-step1: cyoa-step1.cpp $(STEP1_SRC)
	g++ -Wall -Werror -pedantic --std=gnu++98 -g cyoa-step1.cpp page.cpp option.cpp utility.cpp -o cyoa-step1
cyoa-step2: cyoa-step2.cpp $(SRC)
	g++ -Wall -Werror -pedantic --std=gnu++98 -g cyoa-step2.cpp graph.cpp story.cpp page.cpp option.cpp utility.cpp -o cyoa-step2
cyoa-step3: cyoa-step3.cpp $(SRC)
	g++ -Wall -Werror -pedantic --std=gnu++98 -g cyoa-step3.cpp graph.cpp story.cpp page.cpp option.cpp utility.cpp -o cyoa-step3
cyoa-step4: cyoa-step4.cpp $(SRC)
	g++ -Wall -Werror -pedantic --std=gnu++98 -g cyoa-step4.cpp graph.cpp story.cpp page.cpp option.cpp utility.cpp -o cyoa-step4


graph-test: graph.hpp graph.cpp graph_test.cpp
	g++ -Wall -Werror -pedantic --std=gnu++98 -g graph.cpp graph_test.cpp -o $@
story3-test: story3-test.cpp $(SRC)
	g++ -Wall -Werror -pedantic --std=gnu++98 -g story3-test.cpp graph.cpp story.cpp page.cpp option.cpp utility.cpp -o $@

.PHONY: clean
clean:
	rm $(TARGET)
