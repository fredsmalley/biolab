import sys
import glob

#configuration
id_file = "../in/participants.tsv"
id_state_file = "../out/id_state_0.txt"
id_state_dieases = "../out/id_state_diseases_1.txt"
disease_file_dir = "../in/DiseaseSurvey/"

#participants' key
state = "state"
diseases = "diseases"
participants_key = []
participants_key.append(state)
participants_key.append(diseases)

participants = {}
# build dictionay from id file
with open(id_file, 'r') as f:
  for line in f.readlines():
    id = line.split()
    #participants[id[0]] = {}
    participants[id[0]] = {diseases:""}
    #print id[0]
    

# add state information from 
with open(id_state_file) as f:
    for line in f.readlines():
        l = line.split()
        if len(l) > 1:
          participants[l[0]][state] = l[1]
        else:
          participants[l[0]][state] = ""
        #print participants[l[0]]["state"]


# read diseases survery file

for disease_file in glob.glob(disease_file_dir+"*DiseaseSurvey*.csv"):
    print disease_file
    with open(disease_file, 'r') as f:
        for line in f.readlines():
            participant = line.split(',')
            if participant[0] in participants:
                if len(participant[3]) > 0:
                    participants[participant[0]][diseases] = participants[participant[0]][diseases]+participant[3]
                else:
                    participants[participant[0]][diseases] = "" 


# output file
with open(id_state_dieases, 'w') as f:
    for (id, dic) in participants.iteritems():
        if diseases in dic:
            f.write("%s\t%s\t%s\n" % (id, dic[state], dic[diseases]));
