documentation:
	rm -rf docs/* latex/*
	doxygen Doxyfile

cleanData:
	rm -rf data/*

installDeps:
	cd build && conan install .. && bundle binstubs --all

buildDb:
	rm -rf cmake-build && mkdir cmake-build && cd cmake-build && cmake .. && make

runDb: buildDb
	./cmake-build/src/sqlLiteClone

tests: buildDb
	./bin/rspec