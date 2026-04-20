class MiniJVM:
    def __init__(self):
        self.stack = []
        self.variables = {}

    def run(self, filepath):
        with open(filepath, "r") as f:
            for line in f:
                parts = line.strip().split()

                if not parts:
                    continue

                instr = parts[0]

                if instr == "PUSH":
                    self.stack.append(int(parts[1]))

                elif instr == "LOAD":
                    self.stack.append(self.variables[parts[1]])

                elif instr == "STORE":
                    self.variables[parts[1]] = self.stack.pop()

                elif instr == "ADD":
                    b = self.stack.pop()
                    a = self.stack.pop()
                    self.stack.append(a + b)

                elif instr == "SUB":
                    b = self.stack.pop()
                    a = self.stack.pop()
                    self.stack.append(a - b)

                elif instr == "MUL":
                    b = self.stack.pop()
                    a = self.stack.pop()
                    self.stack.append(a * b)

                elif instr == "DIV":
                    b = self.stack.pop()
                    a = self.stack.pop()
                    self.stack.append(a // b)

                elif instr == "PRINT":
                    print(self.stack.pop())


if __name__ == "__main__":
    vm = MiniJVM()
    vm.run("../output/out.bytecode")