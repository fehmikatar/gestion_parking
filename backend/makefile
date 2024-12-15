# Define the output program and object files
gestion_agent: agent.o main.o
    gcc agent.o main.o -o gestion_agent

# Rule to compile main.c into main.o
main.o: main.c
    gcc -c main.c

# Rule to compile agent.c into agent.o
agent.o: agent.c
    gcc -c agent.c

