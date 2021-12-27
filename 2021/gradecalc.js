// Standard grading elements
var columns = new Array("Score","Possible","Percent","Weight","Bonus","WeightedScore");
var header = "<th>Assignment</th> <th>Score</th> <th>Possible</th> <th>Percent</th> <th>Weight</th> <th>Bonus</th> <th>Weighted<br/> Score</th>  ";  

function Assignment(id,possible,weight,special){
    return {Id: id, Possible: possible, Weight: weight, Special: special};
}

var model = [
    Assignment("Project 1", 100, 20/5, false),
    Assignment("Project 2", 100, 20/5, false),
    Assignment("Project 3", 100, 20/5, false),
    Assignment("Project 4", 100, 20/5, false),
    Assignment("Project 5",  50, 20/5, false),
    // Assignment("Project Total (450 max)", 450, 20, false),
    Assignment("Exam 1", 60, 15, false),
    Assignment("Exam 2", 60, 15, false),
    Assignment("Exam 3", 60, 15, false),
    Assignment("Final Exam", 80, 15, false),
    Assignment("Total of Top 12 HW Quizzes", 120, 10, false),
    Assignment("Lab Engagement", 13, 0, true),
    Assignment("BonusEngage + Surveys", 0, 0, true),
    Assignment("Project Late Days", 0, 0, true),
    Assignment("<i>Computed Engagement Points</i>", 10, 10, "NoInput"),
    // Assignment("Bonuses", 0, 1, true)
];

// Easier to grab elements by id
function get(e){
    return document.getElementById(e);
}

// does the funky computation of engagement point score based on labs, bonus, late days;
function updateEngagement(a){
    var labidx = 10;
    var labs   = model[labidx+0];
    var bonus  = model[labidx+1];
    var late   = model[labidx+2];
    var engage = model[labidx+3];

    labs.Percent  = 0; labs.WeightedScore  = 0;
    bonus.Percent = 0; bonus.WeightedScore = 0;
    late.Percent  = 0; late.WeightedScore  = 0;

    engage.Score = labs.Score + bonus.Score - late.Score;
    engage.Bonus = 0;
    engage.Percent = engage.Score / engage.Possible;
    if(engage.Score > engage.Possible){
        engage.Percent = 1.0;
        engage.Bonus = (engage.Score - engage.Possible) * 0.25;
    }
    engage.WeightedScore = engage.Percent * engage.Weight + engage.Bonus;
    get(engage.Id+"Score").innerHTML = new Number(engage.Score).toFixed(2);
    get(engage.Id+"Percent").innerHTML = new Number(engage.Percent).toFixed(2);
    get(engage.Id+"WeightedScore").innerHTML = new Number(engage.WeightedScore).toFixed(2);
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
                console.warn("Update: "+a.Id + s);
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
        warning_div.innerHTML = "WARNING: Total weight is "+total_weight;
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
    a.Bonus = 0;

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



