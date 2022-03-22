import sys

def defineType(f, baseName, className, fieldList):
    f.write("class " + className + " : public " + baseName + " {\n")
    f.write("public:\n")

    #constructor
    f.write("\t" + className + "(" + fieldList + ")\n")
    f.write("\t\t: ")
    
    fields = fieldList.split(", ")
    for field in fields:
        name = field.split(" ")[1]
        f.write(name + "(" + name + ")")
        if field != fields[-1]:
            f.write(", ")
    f.write("{}\n")

    #deconstructor
    f.write("\t~" + className + "(){\n")
    for field in fields:
        if "*" in field:
            name = field.split(" ")[1]
            f.write("\t\tif(!" + name + ") " + "delete " + name + ";\n")
    f.write("\t}\n")

    #fields
    f.write("private:\n")
    for field in fields:
        f.write("\t" + field + ";\n")
    
    f.write("};\n")



def defineAst(outputDir, baseName, types):
    path = outputDir + "/" + baseName + ".hpp"

    f = open(path, 'w')
    
    f.write("#pragma once\n")
    f.write("\n")
    f.write("class " + baseName + " {\n")
    f.write("public:\n")
    f.write("\tvirtual ~" + baseName + "(){}\n")
    f.write("};\n")

    f.write("\n")

    for type in types:
        className = type.split(":")[0].strip()
        fields = type.split(":")[1].strip()
        defineType(f, baseName, className, fields)
        f.write("\n")
    

if len(sys.argv) != 2:
    print("Usage: generate_ast <output directory>")
    sys.exit(64)

outputDir = sys.argv[1]

defineAst(outputDir, "Expr", [
    "Binary     : Expr* left, Token op, Expr* right",
    "Grouping   : Expr* expression",
    "Literal    : Object* value",
    "Unary      : Token op, Expr* right"
])
