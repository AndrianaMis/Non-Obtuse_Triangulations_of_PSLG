from concurrent.futures import ThreadPoolExecutor
import json
import os
import time



categories = {

     "A": [
        ".vscode/challenge_instances_cgshop25/point-set_10_c04b0024.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_20_0c4009d9.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_40_1b92b629.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_60_9fc02edd.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_80_1675b331.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_100_0245ce31.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_150_982c9ab3.instance.json",
        ".vscode/challenge_instances_cgshop25/point-set_250_3c338713.instance.json"
    ],
    "B": [
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_10_46c44a43.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior_10_74050e4d.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_20_1e719235.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_40_84415804.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_60_28a85662.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_100_8d1c2e30.instance.json"
        
    ],
    "C": [
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_250_eb5ab92f.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_20_52abeef5.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_40_5faf6985.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_60_53ad6d23.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_80_f6e462fb.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_100_8ff7a64d.instance.json",

        
    ],

    "D": [
       ".vscode/challenge_instances_cgshop25/ortho_40_df58ce3b.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_60_5c5796a0.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_80_06ee55d4.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_100_bd1e4a14.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_150_53eb4022.instance.json",
        ".vscode/challenge_instances_cgshop25/ortho_250_3b977f7e.instance.json"
       
    ],
    "E": [
        ".vscode/challenge_instances_cgshop25/simple-polygon_10_297edd18.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_20_4bd3c2e5.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_60_0347cd75.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_80_7b8f6c4c.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_100_6101abad.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_150_f24b0f8e.instance.json",
        ".vscode/challenge_instances_cgshop25/simple-polygon_250_6e9d9c26.instance.json",
       
    ],
}

instances=[ 
    ".vscode/challenge_instances_cgshop25/point-set_100_05594822.instance.json",
    ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_40_84415804.instance.json",
    ".vscode/challenge_instances_cgshop25/simple-polygon-exterior-20_250_eb5ab92f.instance.json",
    ".vscode/challenge_instances_cgshop25/ortho_150_53eb4022.instance.json",
    ".vscode/challenge_instances_cgshop25/simple-polygon_100_cb23308c.instance.json"

]
algorithms = ["ls", "sa", "ant"]

def modify_json(input_file, method_value, output_file):
    with open(input_file, "r") as f:
        data = json.load(f)
    data["method"] = method_value  # Update the "method" field
    data["delaunay"] = True
    data["parameters"] = {
        "alpha": 3.0, "beta": 0.8, "xi": 1.0, "psi": 3.0,
        "lambda": 0.5, "kappa": 8, "L": 200
    }
    
    with open(output_file, "w") as f:
        json.dump(data, f, indent=4)

# Function to execute the program and store results in unique files
def run_example(input_file, algorithm, output_file, result_file):
    command = f"./example -i {input_file} -o {output_file}"
    print(f"Running: {command}")
    with open(result_file, "w") as result_out:
        # Redirect stdout and stderr to the result file
        process = os.system(command + f" >> {result_file} 2>&1")
    return f"Finished: {command}, Exit Code: {process}"

inps=[]


def remove_unecessary():
    for inp in inps:
        print(f'removing {inp}!!!')
        os.remove(inp)



# Run all combinations in parallel
def run_all1():
    #with ThreadPoolExecutor(max_workers=8) as executor:

    for cat, insts in categories.items():  # Loop through each category and its instances
        i=0
        for instance in insts:  # Loop through each instance in the category
            i+=1
            for algorithm in algorithms: 
                # Generate unique file names for the temporary input, output, and results
                temps=f".vscode/temp_{i}_{algorithm}.json"
                modify_json(instance, algorithm, temps)
                output_file = f".vscode/output_{i}_{algorithm}.json"
                result_file = f".vscode/results_proj/results_{cat}_{i}_{algorithm}.txt"
                if i==1: inps.append(temps)
                    # Submit the execution task to the thread pool
                run_example( temps, algorithm, output_file, result_file)
               # time.sleep(4)


def run_all():
    i=0
    for instance in instances:
        
        i=i+1
        for algorithm in algorithms:
            # Generate unique file names for the temporary input, output, and results
            temps=f".vscode/temp_{i}_{algorithm}.json"
            modify_json(instance, algorithm, temps)
            output_file = f".vscode/output_{i}_{algorithm}.json"
            result_file = f".vscode/results/results_{i}_{algorithm}.txt"
            inps.append(temps)
                # Submit the execution task to the thread pool
            run_example( temps, algorithm, output_file, result_file)
            #time.sleep(4)



      
if __name__ == "__main__":
    #modify_inputs()
   # run_all1()
    remove_unecessary()