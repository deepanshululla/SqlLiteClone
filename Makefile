documentation:
	rm -rf docs/* latex/*
	doxygen Doxyfile

cleanData:
	rm -rf data/*

installDeps:
	cd build && conan install ..


tests:
	bundle exec rpec