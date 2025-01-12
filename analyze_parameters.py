
import numpy as np
import json
import os

Ls = [20,30,50,100,150]
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
        "alpha": 2.0, "beta": 5.0, "xi": 1.0, "psi": 3.0,
        "lambda": 0.5, "kappa": 10, "L": L
    }
    
    with open(output_file, "w") as f:
        json.dump(data, f, indent=4)

inps=[]
instance= ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_60_28a85662.instance.json"
def run_all():
    #with ThreadPoolExecutor(max_workers=8) as executor:

    for method in methods:
    
        for L in Ls:
            # Generate unique file names for the temporary input, output, and results
            temps=f".vscode/temp_{L}_{method}.json"
            modify_json(instance, method, temps, L)
            output_file = f".vscode/output_{L}_{method}.json"
            result_file = f".vscode/results_{L}_{method}.txt"
            inps.append(temps)
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
methodNames=["Simulated Annealing(SA)", "Local Search (LS)", "Ant Colony (ANT)"]

def graph():
    initial_obt = 0
    initial_vert = 1
    final_obt = 0
    final_vert = 1
    for method in methods:
        for L in Ls:
          
            with open(f'.vscode/results_{L}_{method}.txt', 'r') as file:
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
                print(f'{method} -> {L} -> {diff}: {final_obt}, {final_vert} ')

                if method=="sa":
                    percent_changes_sa.append(diff)
                elif method=="ls":
                    percent_changes_ls.append(diff)
                elif method=="ant":
                    percent_changes_ant.append(diff)

    percent_changes = [percent_changes_sa, percent_changes_ls, percent_changes_ant]
    print(percent_changes[1])
    # Δημιουργία ξεχωριστού γραφήματος για κάθε μέθοδο
    for i, method in enumerate(methodNames):
        plt.figure(figsize=(8, 5))
        plt.bar(Ls, percent_changes[i], color='skyblue', edgecolor='black', alpha=0.8)
        plt.title(f"Percent Change vs L for {method}", fontsize=14)
        plt.xlabel("L Values", fontsize=12)
        plt.ylabel("Percent Change (%)", fontsize=12)
        plt.xticks(Ls)
        plt.grid(axis='y', linestyle='--', alpha=0.6)
        plt.tight_layout()
        plt.show()   

         
if __name__ == "__main__":
    run_all()
    remove_unecessary()
    graph()