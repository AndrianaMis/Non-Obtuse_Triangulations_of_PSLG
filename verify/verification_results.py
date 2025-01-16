import json
from cgshop2025_pyutils.data_schemas.instance import Cgshop2025Instance
from cgshop2025_pyutils.data_schemas.solution import Cgshop2025Solution
from verifier import verify  

with open(".vscode/input_part2.json", "r") as input_file:
    input_data = json.load(input_file)

instance = Cgshop2025Instance(
    instance_uid=input_data["instance_uid"],  # Προσθήκη του πεδίου instance_uid
    num_points=input_data["num_points"],  # Προσθήκη του πεδίου num_points
    points_x=input_data["points_x"],
    points_y=input_data["points_y"],
    region_boundary=input_data["region_boundary"],
    num_constraints=input_data["num_constraints"],
    additional_constraints=input_data["additional_constraints"]
)

with open(".vscode/output_part2.json", "r") as output_file:
    output_data = json.load(output_file)

solution = Cgshop2025Solution(
    instance_uid=input_data["instance_uid"],
    steiner_points_x=[str(x) for x in output_data["steiner_points_x"]],
    steiner_points_y=[str(y) for y in output_data["steiner_points_y"]],
    edges=output_data["edges"]
)

verification_result = verify(instance, solution, strict=True)

print(verification_result)