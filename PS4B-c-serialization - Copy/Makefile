# GIT configuration for distributing the stage a assignment template
REPO_SERVICE=$(shell cat ../../config/repo_service)
REPO_TEMPLATE_ORG=$(shell cat ../../config/repo_org)
# GITHUB CLASSROOM
GITHUB_CLASS_URL=$(shell cat ../../config/github_classroom)

# Assignment specific values
NAME := PS4B

# list of files handout files to create
handoutfiles := handout/README.md 

handout: 
	mkdir -p handout/python_example && cp -r src/python_example/* handout/python_example
	mkdir -p handout/ && cp src/*.c handout/
	mkdir -p handout/ && cp src/*.h handout/
	mkdir -p handout/ && cp src/Makefile handout/
	mkdir -p handout/ && cp src/test.sh handout/
	mkdir -p handout/ && cp src/.gitignore handout/
	mkdir -p handout/ && cp README.md handout/README.md



####  You should not have to change the rest

REPO_TEMPLATE=git@$(REPO_SERVICE):$(REPO_TEMPLATE_ORG)/$(NAME)

.DEFAULT_GOAL = all

.PHONY: all src sol autograder handout template pushtemplate clean 

all: src autograder handout template


sol: ${solfiles}
	-tar -cf sol.tar sol

src:
	make -C src

autograder:
	make -C gradescope

template: handout
	mkdir -p template/$(NAME) && cp -r handout/* template/$(NAME)
	cd template/${NAME} && git init
	-cd template/${NAME} && git add . && git commit -m "initial commit" && git branch -M main
	-cd template/${NAME} && git remote add origin $(REPO_TEMPLATE)
	@echo "create repo $(NAME) at  https://$(REPO_SERVICE)/organizations/$(REPO_TEMPLATE_ORG)/repositories/new"
	@echo "then run make pushtemplate"

pushtemplate:
	cd template/${NAME} && git push -f -u origin main
	@echo "don't forget to visit $(GITHUB_CLASS_URL) to create assignment from the template"

clean:
	rm -rf $(wildcard handout sol.tar *~)
	make -C src clean
	make -C gradescope clean

distclean: clean
	rm -rf $(wildcard template)
