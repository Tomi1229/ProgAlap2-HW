const svg = d3.select("#network-container")
    .append("svg")
    .attr("width", "100%")
    .attr("height", "100%")
    .attr("viewBox", "0 0 1000 800")
    .attr("preserveAspectRatio", "xMidYMid meet");

const g = svg.append("g"); // minden elem ide kerül

svg.call(d3.zoom().on("zoom", function (event) {
    g.attr("transform", event.transform);
}));

const nodeIcons = {
    "PowerPlant": "icons/thermoplant.svg",
    "THERMO": "icons/thermoplant.svg",
    "NUCLEAR": "icons/nuclearplant.svg",
    "HYDRO": "icons/hydroplant.svg",
    "WIND": "icons/windpower.svg",
    "BIOMASS": "icons/biomass.svg",
    "SOLAR": "icons/solarplant.svg",
    "City": "icons/city.svg",
    "Industrial": "icons/factory.svg",
    "TransformerStation": "icons/transformstation.svg",
    
};

const carbonColors = {
    "NUCLEAR": "#00BFFF",
    "THERMO": "#FF4500",
    "HYDRO": "#1E90FF",
    "WIND": "#7CFC00",
    "BIOMASS": "#8B4513",
    "SOLAR": "#FFD700",
};

d3.json("network.json").then(data => {
    const edgeCount = {};
    data.edges.forEach(edge => {
        const src = typeof edge.source === 'object' ? edge.source.id : edge.source;
        const tgt = typeof edge.target === 'object' ? edge.target.id : edge.target;
        edgeCount[src] = (edgeCount[src] || 0) + 1;
        edgeCount[tgt] = (edgeCount[tgt] || 0) + 1;
    });

    const centralNodes = Object.entries(edgeCount)
        .sort((a, b) => b[1] - a[1])
        .slice(0, 3)
        .map(entry => entry[0]);

    const linkGroup = g.append("g").attr("class", "links");
    const nodeGroup = g.append("g").attr("class", "nodes");

    const links = linkGroup.selectAll("line")
        .data(data.edges)
        .enter()
        .append("line")
        .attr("stroke-width", 3)
        .attr("stroke", d => {
            const source = data.nodes.find(n => n.id === d.source || n.id === d.source.id);
            if (source && source.plantType && carbonColors[source.plantType.toUpperCase()]) {
                return carbonColors[source.plantType.toUpperCase()];
            }
            return "#999";
        });

    const powerlineIcons = linkGroup.selectAll("image")
        .data(data.edges)
        .enter()
        .append("image")
        .attr("xlink:href", "icons/powerline.svg")
        .attr("width", 60)
        .attr("height", 60);

    const node = nodeGroup.selectAll("g")
        .data(data.nodes)
        .enter()
        .append("g")
        .attr("class", "node")
        .call(d3.drag()
            .on("start", dragStarted)
            .on("drag", dragged)
            .on("end", dragEnded));

    node.append("image")
        .attr("xlink:href", d => nodeIcons[d.plantType?.toUpperCase()] || nodeIcons[d.type] || "icons/default.svg")
        .attr("x", -20)
        .attr("y", -20)
        .attr("width", 80)
        .attr("height", 80);

    node.append("text")
        .text(d => d.id)
        .attr("y", 80)
        .attr("text-anchor", "middle")
        .attr("font-size", "12px");

    
    data.nodes.forEach(d => {
        if (centralNodes.includes(d.id)) {
            d.fx = 500;
            d.fy = 400;
        }
    });

    const simulation = d3.forceSimulation(data.nodes)
        .force("link", d3.forceLink(data.edges).id(d => d.id).distance(200))
        .force("charge", d3.forceManyBody().strength(-300))
        .force("x", null)
        .force("y", null)
        .force("center", null)
        .on("tick", () => {
            links
                .attr("x1", d => d.source.x)
                .attr("y1", d => d.source.y)
                .attr("x2", d => d.target.x)
                .attr("y2", d => d.target.y);

            powerlineIcons
                .attr("x", d => (d.source.x + d.target.x) / 2 - 12)
                .attr("y", d => (d.source.y + d.target.y) / 2 - 12);

            node
                .attr("transform", d => `translate(${d.x},${d.y})`);
        })
        .on("end", () => {
            const bounds = g.node().getBBox();
            const fullWidth = 1000;
            const fullHeight = 800;
            const width = bounds.width;
            const height = bounds.height;
            const midX = bounds.x + width / 2;
            const midY = bounds.y + height / 2;

            const scale = 0.85 / Math.max(width / fullWidth, height / fullHeight);
            const translate = [fullWidth / 2 - scale * midX, fullHeight / 2 - scale * midY];

            svg.transition()
                .duration(750)
                .call(
                    d3.zoom().transform,
                    d3.zoomIdentity.translate(translate[0], translate[1]).scale(scale)
                );
        });

    function dragStarted(event, d) {
        if (!event.active) simulation.alphaTarget(0.3).restart();
        d.fx = d.x;
        d.fy = d.y;
    }

    function dragged(event, d) {
        d.fx = event.x;
        d.fy = event.y;
    }

    function dragEnded(event, d) {
        if (!event.active) simulation.alphaTarget(0);
        if (!centralNodes.includes(d.id)) {
            d.fx = null;
            d.fy = null;
        }
    }
});