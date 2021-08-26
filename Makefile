documentation:
	rm -rf docs/* latex/*
	doxygen Doxyfile

cleanData:
	rm -rf data/*

installDeps:
	cd build && conan install ..

buildDb:
	mkdir cmake-build || cd cmake-build && cmake .. && make

runDb: buildDb
	./cmake-build/src/sqlLiteClone

tests:
	bundle exec rpec