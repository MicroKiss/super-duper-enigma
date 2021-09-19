from os import listdir
import json
from os.path import isfile, join
onlyfiles = [f for f in listdir("./memes") if isfile(join("./memes", f))]

for i in range(len(onlyfiles)):
    onlyfiles[i] = "./memes/"+onlyfiles[i]


file = open("imgnames.js", "w")

file.write("var images = {};\n")

file.write("images =")
file.write(json.dumps(onlyfiles))
file.write("\n")
file.write("export default images;")

file.close()
