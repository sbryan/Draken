# How to add a new printer
Instructions from [Spark Developer Reference](https://spark.autodesk.com/developers/reference/introduction/printer-manufacturers-2/integrate-your-printer-model)

- Choose a printer name

        Draken-slot3-50um

- Create a model for the print bed

        Draken-slot3-50um.obj

- Add brand logo and printer icons

        Draken.png
        Draken-slot3-50um100x100.png
        Draken-slot3-50um50x50.png

- Add your printer to printertypes.json ([PrinterType referece](https://jsapi.apiary.io/apis/sparkprint1/reference/print-definitions/printer-types.html))

        {
            "id" : "<SOME GUID>",
            "version": 1,
            "name": "Draken - slot 3 (50um)",
            "manufacturer": "3D Facture",
            "model_number": "1.0.0",
            "registration_url" : null,
            "icon_id": "data/Draken.png",
            "icon50x50_id": "data/Draken-slot3-50um50x50.png",
            "icon100x100_id": "data/Draken-slot3-50um100x100.png",
            "technology": "DLP",
            "default_material_id": "<SOME MATERIAL ID>",
            "default_profile_id": "<SOME PROFILE ID>",
            "firmware": {
                "type": "draken",
                "version": "1.0.0"
            },
            "build_volume": {
                "type": "Cartesian",
                "bed_size": [
                    96.00000000000000,
                    54.00000000000000,
                    190.0000000000000
                ],
                "bed_offset": [
                    -3.200000000000000,
                    -2.000000000000000,
                    0.000000000000000
                ],
                "home_position": [0, 0, 0],
                "park_position": [0, 0, 0],
                "bed_file_id": "data/draken-slot3-50um.zip"
            },
            "max_materials": 1,
            "printable": {
                "content": "image/png+tar.gz",
                "thumbnail": "image/png",
                "extension": "tar.gz",
                "generates_supports": false,
                "packager_file_id": "data/EmberPackager.lua"
            },
            "supported_connections": [
                {
                    "type": "TCP-IP",
                    "protocol": "_http._tcp",
                    "info" : {
                        "port": 9091,
                        "api": {
                            "name": "CWH",
                            "version": "1.0.0"
                        }
                    }
                }
            ],
            "preferred_connection": "TCP-IP",
            "max_speeds": {
                "z": 0.1
            },
            "software_info": {
                "name": "Creation Workshop",
                "url": "http://www.envisionlabs.net/"
            },
            "printer_capabilities": {},
            "_files": [
                "icon_id",
                "icon50x50_id",
                "icon100x100_id",
                "build_volume.bed_file_id",
                "printable.packager_file_id"
            ]
        }

- If needed, add material type to materials.json  ([Materials referece](https://jsapi.apiary.io/apis/sparkprint1/reference/print-definitions/materials.html)):

        {
            "id" : "<SOME GUID>",
            "version" : 1,
            "color" : "red"
            "name" : "G+ (Red)",
            "manufacturer": "MakerJuice",
            "website": "http://www.makerjuice.com/shop/gplus/",
            "technology" : "DLP",
            "composition" : "PHOTORESIN",
            "printer_types": [
                "<ID compatible PrinterType>"
            ],
            "cost" : 55,
            "rating" : 5,
            "opacity" : 2,
            "tags" : [],
            "pct_shrink" : null,
            "is_user": false,
            "FirstExposureSec" : 6,
            "BurnInLayers" : 4,
            "BurnInExposureSec" : 6,
            "ModelExposureSec" : 3,
            "density" : 0,
            "color" : "red"
        }

- Add a default slicing profile to profiles.json  ([Profiles referece](https://jsapi.apiary.io/apis/sparkprint1/reference/print-definitions/profiles.html))

        {   // Required settings
            "id": "<SOME GUID>",
            "name": "Clear Medium Quality/Speed",
            "technology": "DLP",
            "version": 1,
            "printer_types": [
                "<ID compatible PrinterType>"
            ],
            "layer_height": 0.0025,
            "support_angle_tol": 1.047197551196598,
            "support_contact_tol": 0.001,
            "support_min_radius": 0.1,
            "support_min_separation": 0,
            
            // Additional settings as appropriate
            "brightness_blur_radius": 12,
            "brightness_input_max": 0.25,
            "brightness_input_min": 0.01,
            "brightness_output_max": 0.7,
            "brightness_output_min": 1,
            "burn_in_exposure": 4,
            "burn_in_layer_angle_of_rotation": 1.0472,
            "burn_in_layer_approach_slide_velocity": 2,
            "burn_in_layer_approach_z_axis_velocity": 0.05,
            "burn_in_layer_separation_slide_velocity": 2,
            "burn_in_layer_separation_z_axis_velocity": 0.05,
            "burn_in_layer_wait_after_approach": 0.5,
            "burn_in_layer_wait_after_exposure": 0,
            "burn_in_layer_wait_after_separation": 0,
            "burn_in_layer_z_axis_overlift": 0.025,
            "burn_in_layers": 4,
            "first_layer_angle_of_rotation": 1.0472,
            "first_layer_approach_slide_velocity": 2,
            "first_layer_approach_z_axis_velocity": 0.05,
            "first_layer_exposure_time": 8,
            "first_layer_separation_slide_velocity": 2,
            "first_layer_separation_z_axis_velocity": 0.05,
            "first_layer_wait_after_approach": 0.5,
            "first_layer_wait_after_exposure": 0,
            "first_layer_wait_after_separation": 0,
            "first_layer_z_axis_overlift": 0.025,
            "img_height": 800,
            "img_width": 1280,
            "layer_height_first": 0.2,
            "model_exposure_time": 2.2,
            "model_layer_angle_of_rotation": 1.0472,
            "model_layer_approach_slide_velocity": 12,
            "model_layer_approach_z_axis_velocity": 0.05,
            "model_layer_separation_slide_velocity": 12,
            "model_layer_separation_z_axis_velocity": 0.05,
            "model_layer_wait_after_approach": 0.5,
            "model_layer_wait_after_exposure": 0,
            "model_layer_wait_after_separation": 0,
            "model_layer_z_axis_overlift": 0.025,
            "support_base_length": 0.3,
            "support_base_radius": 0.3,
            "support_bed_standoff": 0.3,
            "support_clearance": 0.01,
            "support_horizontal_connection_size": 0,
            "support_layer_height": 0.001,
            "support_max_angle": 0.6108652381980153,
            "support_object_top_connections": 1,
            "support_offset": -0.01,
            "support_post_radius": 0.05,
            "support_sampling_density": 0.3,
            "support_tip_length": 0.1,
            "support_tip_penetration_distance": -0.0025,
            "support_tip_radius": 0.03
        }

- Add mapping of printer commands to the driver folder
