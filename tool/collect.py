import sys
import glob

#configuration
id_file = "../in/participants.tsv"
id_state_file = "../out/id_state_0.txt"
id_diseases = "../out/id_diseases.tsv"
disease_file_dir = "../in/DiseaseSurvey/"
state_name = "../in/states"

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
    #read state abbreviations
    state_abbreviation = {}
    with open(state_name) as s:
        for line in s.readlines():
            state_name_map = line.strip("\n").split(':')
            state_abbreviation[state_name_map[0]] = state_name_map[1]
            #print line[0] + "--> " + line[1]

    
    for line in f.readlines():
        l = line.strip("\n").split('\t')
        if len(l) > 1 and l[1] != '':
          participants[l[0]][state] = state_abbreviation[l[1]]
        else:
          participants[l[0]][state] = ""
        #print participants[l[0]]["state"]


# read diseases survery file
#for disease_file in glob.glob(disease_file_dir+"*DiseaseSurvey*.csv"):
    #print disease_file
    disease_file = disease_file_dir+"PGPTrait&DiseaseSurvey2012_Cancers-20150206200050.csv"
    with open(disease_file, 'r') as f:
        for line in f.readlines():
            # line format in DiseaseSurvey:
            # id, data time, xxxx, diseases
            participant = line.strip(",\n").split(',')
            if participant[0] in participants:
                if len(participant) > 3:
                    all_diseases = []
                    for d in participant[3:]:
                        if d != '':
                            all_diseases.append(d.strip("\" "))
                    #print all_diseases
                    participants[participant[0]][diseases] = all_diseases
                # no content
                else:
                    participants[participant[0]][diseases] = "" 


# output file
with open(id_diseases, 'w') as f:
    for (id, dic) in participants.iteritems():
        if diseases in dic:
            f.write("%s\t" % (id))
            for d in dic[diseases]:
                f.write("%s," % d)
            f.write("\n")
        else:
            f.write("%s\t%s\n" % (id, None))
