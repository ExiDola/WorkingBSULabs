import React, { Component } from 'react';
import './styles.css';

class Regions extends Component {
  constructor(props) {
    super(props);
    this.state = {
      substr: '',
      regions: window.lab9models.regionsModel(),
      filteredRegions: window.lab9models.regionsModel(),
    };

    this.handleChange = this.handleChange.bind(this);
  }

  handleChange(event) {
    const substr = event.target.value.toLowerCase();
    const filteredRegions = this.state.regions.filter(region =>
      region.toLowerCase().includes(substr)
    );

    this.setState({
      substr: event.target.value,
      filteredRegions,
    });
  }

  render() {
    return (
      <div className="container">
        <h1>Phone Models</h1>
        <div className="motto-update">
          <label htmlFor="substrId">Enter substring to search:</label>
          <input
            id="substrId"
            type="text"
            value={this.state.substr}
            onChange={this.handleChange}
          />
          <p>Current substring: {this.state.substr}</p>
        </div>

        {this.state.filteredRegions.length > 0 ? (
          <ul>
            {this.state.filteredRegions.map((region, index) => (
              <li key={index}>{region}</li>
            ))}
          </ul>
        ) : (
          <p>No phone models match the given substring.</p>
        )}
      </div>
    );
  }
}

export default Regions;
