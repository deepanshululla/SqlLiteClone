documentation:
	rm -rf docs/* latex/*
	doxygen Doxyfile

cleanData:
	rm -rf data/*