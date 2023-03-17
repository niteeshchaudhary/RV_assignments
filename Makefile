compilecreator: src/creator.cpp
	g++ src/creator.cpp -o bin/creator.out

compilemonitor: test_monitor.cpp
	g++ test_monitor.cpp -o bin/test_monitor.out

compile: src/monitor2.cpp
	g++ src/monitor2.cpp -o bin/monitor2.exe

dev:
	@echo "Niteesh Kamal Chaudhary"
	@echo "Roll No. 200010035"