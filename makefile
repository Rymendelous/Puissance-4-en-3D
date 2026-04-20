# Compilateur et flags
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -Wextra -g -MMD -MP
INCLUDES := -I./include

# Dossiers
SRCDIR   := src
OBJDIR   := obj
BINDIR   := bin

# Cible finale
TARGET   := $(BINDIR)/puissance4
TEST_TARGET := $(BINDIR)/test_suite

# Détection automatique des sources et objets
SRCS     := $(wildcard $(SRCDIR)/*.cpp)
OBJS     := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))
DEPS 	 := $(OBJS:.o=.d)

# Règle par défaut
all: $(TARGET)
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Édition de liens
$(TARGET): $(filter-out $(OBJDIR)/test.o, $(OBJS)) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@
$(TEST_TARGET): $(filter-out $(OBJDIR)/main.o, $(OBJS)) | $(BINDIR)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation des .o depuis les .cpp
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Création des dossiers si absents
$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BINDIR):
	mkdir -p $(BINDIR)

# Nettoyage
clean:
	rm -rf $(OBJDIR) $(BINDIR)

# Rebuild complet
re: clean all

# Pour éviter les conflits avec des fichiers nommés "all", "clean", etc.
.PHONY: all clean re test

-include $(DEPS)