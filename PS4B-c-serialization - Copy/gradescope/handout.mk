TARGETS = test game
LIBS = serialize buffer serialize_custom file_loader
LDFLAGS = -lm -O0
BUILDDIR = build
BUILD_TARGETS = $(addprefix $(BUILDDIR)/,$(TARGETS))
OBJS = $(addprefix $(BUILDDIR)/,$(addsuffix .o,$(TARGETS) $(LIBS)))
LIBOBJS = $(addprefix $(BUILDDIR)/,$(addsuffix .o,$(LIBS)))

all: $(BUILD_TARGETS)

$(BUILD_TARGETS): $(BUILDDIR) $(OBJS)
	gcc -o $@ $@.o $(LIBOBJS) $(LDFLAGS) -W -Wall -g

$(BUILDDIR):
	mkdir $(BUILDDIR)

$(BUILDDIR)/%.o: %.c
	gcc -o $@ -c $< -W -Wall -g

clean:
	rm *~ -rf $(BUILDDIR)
