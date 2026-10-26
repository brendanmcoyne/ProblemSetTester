src=test.sh test.c
autograder.zip: run_autograder handout.mk setup.sh test_gradescope.sh ${src}
	chmod +x test.sh
	zip -r $@ $?

# autograder_bonus.zip: run_autograder handout.mk setup.sh test_gradescope_bonus.sh test_bonus.sh ${src}
# 	chmod +x test_bonus.sh
# 	zip -r $@ $?

.PHONY: ${src}

${src}: $(src:%=../src/%) 
	cp $(src:%=../src/%) .

handout.mk: ../src/Makefile
	cp $< $@

clean:
	-rm -f $(wildcard autograder.zip autograder_bonus.zip ${src} *~)

