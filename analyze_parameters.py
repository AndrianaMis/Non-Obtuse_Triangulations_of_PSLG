
import numpy as np
import json
import os

Ls = [30,50,100,150, 200, 300]
methods=["ls", "sa", "ant"]


def run_example(input_file, algorithm, output_file, result_file):
    command = f"./example -i {input_file} -o {output_file}"
    print(f"Running: {command}")
    with open(result_file, "w") as result_out:
        # Redirect stdout and stderr to the result file
        process = os.system(command + f" >> {result_file} 2>&1")
    return f"Finished: {command}, Exit Code: {process}"


def modify_json(input_file, method_value, output_file, L):
    with open(input_file, "r") as f:
        data = json.load(f)
    data["method"] = method_value  # Update the "method" field
    data["delaunay"] = True
    data["parameters"] = {
        "alpha": 3.0, "beta": 0.8, "xi": 1.0, "psi": 3.0,
        "lambda": 0.5, "kappa": 8, "L": L
    }
    
    with open(output_file, "w") as f:
        json.dump(data, f, indent=4)

inps=[]
instances= [
            ".vscode/challenge_instances_cgshop25/point-set_60_9fc02edd.instance.json", 
            ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_60_28a85662.instance.json",
            ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_80_f6e462fb.instance.json",
            ".vscode/challenge_instances_cgshop25/ortho_60_f744490d.instance.json",
            ".vscode/challenge_instances_cgshop25/simple-polygon_150_f24b0f8e.instance.json"
            
            ]
def run_all():
    #with ThreadPoolExecutor(max_workers=8) as executor:
    i=0
    for instance in instances:
        i+=1
        for method in methods:
        
            for L in Ls:
                # Generate unique file names for the temporary input, output, and results
                temps=f".vscode/temp_{L}_{method}.json"
                modify_json(instance, method, temps, L)
                output_file = f".vscode/output_{L}_{method}.json"
                result_file = f".vscode/results/results_{i}_{L}_{method}.txt"
                if i==1: inps.append(temps)
                    # Submit the execution task to the thread pool
                run_example( temps, method, output_file, result_file)
                
        
     


def remove_unecessary():
    for inp in inps:
        print(f'removing {inp}!!!')
        os.remove(inp)

      
import matplotlib.pyplot as plt

percent_changes_sa=[]
percent_changes_ls=[]
percent_changes_ant=[]
methodNames=["Local Search (LS)", "Simulated Annealing(SA)", "Ant Colony (ANT)"]

def graph():
    initial_obt = 0
    initial_vert = 1
    final_obt = 0
    final_vert = 1
    
    for method in methods:
        for L in Ls:
            sum_diff=0
            for i,instance in enumerate(instances):
          
                with open(f'.vscode/results/results_{i+1}_{L}_{method}.txt', 'r') as file:
                    lines = file.readlines()
                    for line in lines:
                        if line.startswith("Αρχικές αμβλείες:"):  
                            parts = line.split()
                            initial_obt = float(parts[2].strip())
                        if line.startswith("Αρχικά faces:"):
                            parts = line.split()
                            initial_vert = float(parts[2].strip())
                        if line.startswith("Τελικές αμβλείες:"):  
                            parts = line.split()
                            final_obt =float(parts[2].strip())
                        if line.startswith("Τελικές faces:"):
                            parts = line.split()
                            final_vert = float(parts[2].strip())
                    diff=initial_obt/initial_vert - final_obt/final_vert
                    sum_diff+=diff
            avg_diff=sum_diff/len(instances)
            print(f'{method} -> {L} -> {avg_diff} ')

            if method=="sa":
                percent_changes_sa.append(avg_diff)
            elif method=="ls":
                percent_changes_ls.append(avg_diff)
            elif method=="ant":
                percent_changes_ant.append(avg_diff)


    percent_changes = [percent_changes_ls, percent_changes_sa, percent_changes_ant]
    print(percent_changes[1])
    # Δημιουργία ξεχωριστού γραφήματος για κάθε μέθοδο
    for i, method in enumerate(methodNames):
        plt.figure(figsize=(8, 5))
        plt.bar(Ls, percent_changes[i], color='skyblue', edgecolor='black', alpha=0.8)
        plt.title(f"Percent Changes vs L for {method}", fontsize=14)
        plt.xlabel("L Values", fontsize=12)
        plt.ylabel("Percent Change", fontsize=12)
        plt.xticks(Ls)
        plt.grid(axis='y', linestyle='--', alpha=0.6)
        plt.tight_layout()
        plt.show()   

         
if __name__ == "__main__":
  #  run_all()
   # remove_unecessary()
    graph()