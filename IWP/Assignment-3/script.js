var clickOnce = 0;
$(document).ready(function () {
  $("#moreText").hide();
  $("#heading").css("color", "white").slideUp(2000).slideDown(2000);
});
$(document).ready(function () {
  $("#welcome").click(function () {
    var div = $("#wDiv");
    div.animate({ height: "300px", opacity: "0.2" }, "slow");
    div.animate({ width: "300px", opacity: "0.4" }, "slow");
    div.animate({ height: "50px", opacity: "0.2" }, "slow");
    div.animate({ width: "50px", opacity: "0.4" }, "slow");
    $("#welcome").hide(5000,()=>{
        alert("We are so glad you are here")
    });
    $("#stop").click(function () {
      div.stop(true, true);
    });
    setTimeout(() => {
      $("main").slideDown("slow");
    }, 3000);
  });
});
$("#more").click(function () {
  if (clickOnce === 0) {
    $("#more").text("Hide");
    clickOnce = 1;
  } else {
    $("#more").text("Tell us more about the origin of Umbrella House");
    clickOnce = 0;
  }
  $("#moreText").toggle("slow");
});
$("#prodMore").click(function () {
  $("#a1").fadeIn();
  $("#a2").fadeIn("slow");
  $("#a3").fadeIn(3000);
  $("#a4").fadeIn(3200);
});
$("p").on({
  mouseenter: function () {
    $(this).css("background-color", "lightblue");
    $(this).css("font-size", "large");
  },
  mouseleave: function () {
    $(this).css("background-color", "rgba(10, 44, 83, 0.3)");
    $(this).css("font-size", "medium");
  },
  click: function () {
    $(this).css("background-color", "yellow");
  },
});
$(document).ready(function () {
  $("input:not(input:submit)").focus(function () {
    $(this).css("background-color", "rgba(10, 44, 83, 0.3)");
  });
  $("input:text,input:email").blur(function () {
    $(this).css("background-color", "ligtgrey");
  });
});
$("fieldset").on({
  click: function () {
    $(this).css("background", "rgba(10, 44, 83, 0.2)");
  },
  dblclick: function () {
    $(this).css("background", "rgba(10, 44, 83, 0.3)");
  },
});
$("#a1,#a2,#a3,#a4").hover(
  function () {
    $(this).css("transform", "scale(1.2)");
  },
  function () {
    $(this).css("transform", "scale(1)");
  }
);
$("form").submit(function (event) {
  event.preventDefault();
  alert("Thank you for responding to:" + $("legend").text());
  alert("We will reply to you soon on this email:" + $("#email").val());
  $("form").trigger("reset");
  $("legend").text("You have contacted us already");
  $(':input[type="submit"]').prop("disabled", true);
  $("#success").attr("src", "./img/success.gif");
  $("#success").addClass("sucessImg");
});
$(document).ready(function () {
  $("#myInput").on("keyup", function () {
    var value = $(this).val().toLowerCase();
    $("#myTable tr").filter(function () {
      $(this).toggle($(this).text().toLowerCase().indexOf(value) > -1);
    });
  });
});
$(document).ready(function () {
  $("#myTable tr:even").addClass("highlight");
});
$(function () {
  $("#selectable").selectable();
});
$(function () {
  $("#accordion").accordion();
});
$(function () {
  $("#draggable").draggable();
  $("#droppable").droppable({
    drop: function (event, ui) {
      $(this).addClass("ui-state-highlight");
      $("#save").html("Thank you");
      var div = $("#save");
      div.animate({ fontSize: "3rem" });
      div.animate({ fontSize: "4rem" });
      $("#save").addClass("mb");
    },
  });
});
