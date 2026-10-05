// Standard grading elements
var columns = new Array("Score","Possible","Percent","Weight","WeightedScore");
var header = "<th>Assignment</th> <th>Score</th> <th>Possible</th> <th>Percent</th> <th>Weight</th> <th>Weighted<br/> Score</th>  ";  

function Assignment(id,possible,weight,special){
    return {Id: id, Possible: possible, Weight: weight, Special: special};
}

var model = [
    Assignment("Project 1", 100,  2, false),
    Assignment("Project 2", 100,  2, false),
    Assignment("Project 3", 100,  2, false),
    Assignment("Project 4", 100,  2, false),
    Assignment("Project 5", 100,  2, false),
    Assignment("Labs Total", 10, 10, false),
    Assignment("Exam 1",     70, 20, false),
    Assignment("Exam 2",     70, 20, false),
    Assignment("Exam 3",     70, 20, false),
    Assignment("Final Exam",100, 20, false),
    Assignment("Engagement Points", 0, 0, true),
    // Assignment("<i>Engagement Bonus</i>", 0, 0, "NoInput"),
    // Assignment("Total of Top 10 HW Quizzes", 100, 10, false),
    // Assignment("Project Late Days", 0, 0, true),
    // Assignment("Bonuses", 0, 1, true)
];

// Easier to grab elements by id
function get(e){
    return document.getElementById(e);
}

// computes engagement point bonus as floor(log2(1+EP_Total))
function updateEngagement(a){
    var eps = model.find(as => as.Id=="Engagement Points");
    eps.Percent = 0.0;
    eps.Weight  = 0.0;
    eps.WeightedScore = 0.5 * Math.floor(Math.log2(1.0+eps.Score));
    get(eps.Id+"WeightedScore").innerHTML = new Number(eps.WeightedScore).toFixed(2);
}

// Update screen on pressing button
function updateOnInput(){
    syncInputToModel();
    updateModelNoSpecial();
    updateEngagement();
    syncModelToDisplay();

    var total = 0;         // compute total score
    for(var i in model){
	var a = model[i]
	total += a.WeightedScore;
    }
    get("total").value = new Number(total).toFixed(2);
    get("warning").innerHTML = "";
    warn_on_project_overage();
    warn_on_bad_total_weight();
}

    
// Copy all inputs in the input fields into the corresponding Score
// field of model elements
function syncInputToModel(){
    for(i in model){
        var a = model[i];
        if(a.Special != "NoInput"){
            a.Score = new Number(get(a.Id+"Score").value);
        }
    }
}

// Update non-special model columns, changes current Percent and
// WeightedScore
function updateModelNoSpecial(){
    for(i in model){
        var a = model[i];
        if(a.Special==false){
	    a.Percent = a.Score / a.Possible;
	    a.WeightedScore = a.Percent * a.Weight;
        }
    }
}

// Updates display columns to reflect what the internal model shows
function syncModelToDisplay(){
    for(i in model){
        var a = model[i];
        for(var c in columns){
	    var s = columns[c]
	    if(s!="Score"){
                // console.warn("Update: "+a.Id + s);
	        get(a.Id + s).innerHTML = new Number(a[s]).toFixed(2);
            }
	}
    }
}


// Calculate the total possible weight and warn in a div if it is not
// about 100.0 percent
function warn_on_bad_total_weight(){
    var total_weight = 0;
    for(var i=0; i<model.length; i++){
        total_weight += model[i].Weight;
    }

    if(Math.abs(total_weight - 100.0) > 1e-3){
        var warning_div = get("warning");
        var msg = "WARNING: Total weight is "+total_weight;
        warning_div.innerHTML = warning_div.innerHTML.concat(msg);
    }
}

function warn_on_project_overage(){
    var proj_total = 0;
    for(var i=0; i<model.length; i++){
        if(model[i].Id.match(/Project [0-9]+/)){
            proj_total += model[i].Score;
        }
    }

    if(proj_total > 500){
        var warning_div = get("warning");
        var msg = "WARNING: Project total is "+proj_total+" which exceeds 500 point cap"
        warning_div.innerHTML = warning_div.innerHTML.concat(msg);
    }
}




// Create the grade table
function makeTable(){
    var table = get("gradeTable");
    var head =  table.insertRow(-1);
    head.innerHTML = header;

    for(var i=0; i<model.length; i++){
	addRow(model[i],table);
    }
}

// Add row for given assignment
function addRow(a,table){
    var id = a.Id;
    var row = table.insertRow(-1);
    var el = row.insertCell(-1);
    el.innerHTML = id;
    a.Score = a.Possible;   // initial score and bonus
    // a.Bonus = 0;

    for(var j=0; j<columns.length; j++){
	var el = row.insertCell(-1);
	var col = columns[j];
	if(col=="Score" && a.Special!="NoInput"){
	    var s = '<input size="5" type="text" id="'+id+col+'" value="'+a.Possible+'" />';
	    el.innerHTML = s;
	}
	else if(col=="Score" && a.Special=="NoInput"){
	    var s = '<div width="100" style="font-family:monospace; text-align:right; border:1px solid black;" id="'+id+col+'" />';
	    el.innerHTML = s;
	}
	else {
	    var s = '<div width="100" style="font-family:monospace; text-align:right;" id="'+id+col+'" />';
	    el.innerHTML = s;
	}
    }
}



